"""Arucoマーカを用いたリアカメラのキャリブレーションを行うモジュール.
"""

import json
from typing import Tuple

import cv2
from cv2 import aruco
import numpy as np

from rear_camera.camera_interface import CameraInterface


class Calibrator:
    def __init__(self, camera_interface: CameraInterface = CameraInterface(), trans_mat_file: str = "rear_camera_param.npy", distance_file: str = "rear_camera_distance_param.json") -> None:
        self.__camera_interface = camera_interface
        self.__aruco_dictionary = aruco.getPredefinedDictionary(
            aruco.DICT_4X4_50)
        self.__trans_mat_file = trans_mat_file
        self.__distance_file = distance_file

    def calc_param(self, img: np.ndarray) -> Tuple[np.ndarray, float, float]:
        corners, ids, rejected_img_points = aruco.detectMarkers(
            img, self.__aruco_dictionary)
        if ids is None:
            raise RuntimeError("Could not find markers.")
        trans_mat, distance_from_center_52_5mm, height_offset_from_center = self.__get_transform_mat(
            img, corners, ids)
        return trans_mat, distance_from_center_52_5mm, height_offset_from_center

    def calibrate(self):
        img = self.__camera_interface.capture_image()
        if img is None:
            raise RuntimeError("Could not capture camera image.")
        trans_mat, distance_from_center_52_5mm, height_offset_from_center = self.calc_param(
            img)
        np.save(self.__trans_mat_file, trans_mat)
        distance_data = {
            "distance_from_center_52_5mm": distance_from_center_52_5mm,
            "height_offset_from_center": height_offset_from_center
        }
        with open(self.__distance_file, mode="w") as fp:
            json.dump(distance_data, fp)

    def __get_marker_mean(self, ids, corners, index: int):
        for i, id in enumerate(ids):
            # マーカーのインデックス検索
            if (id[0] == index):
                v = np.mean(corners[i][0], axis=0)  # マーカーの四隅の座標から中心の座標を取得する
                return [v[0], v[1]]
        raise ValueError("Index(%d) not found")

    def __get_transform_mat(self, frame, corners, ids):
        h, w = frame.shape[:2]
        top_coordinate = self.__get_marker_mean(ids, corners, 1)
        bottom_coordinate = self.__get_marker_mean(ids, corners, 6)
        left_coordinate = self.__get_marker_mean(ids, corners, 3)
        right_coordinate = self.__get_marker_mean(ids, corners, 4)
        frame_coordinates = np.float32(
            [top_coordinate, bottom_coordinate, left_coordinate, right_coordinate])

        # NOTE: 射影変換後の画像において、4つのArUcoマーカの中心点と各辺の中点が一致する正方形を考える.
        # - distance_from_center_52_5mm
        #     上記正方形の中心点と各辺の中点を結ぶ線分の距離(pix)、(105/2 mm).
        # - height_offset_from_center
        #     上記正方形の中心点のオフセット、
        #     0の場合上記正方形の中心点と射影変換後の画像の中心点が一致する(pix).
        # 上記正方形の中心点と走行体の中心点(タイヤの軸の中点)の距離は以下のようになる.
        #     105/2 + 40/2 + (301 - 122/2) = 312.5mm
        #  ただし、射影変換後の画像下部より更に下の部分に走行体の原点が存在することに留意すること.
        #  また、現実の座標系と画像の座標の差異にも留意すること.
        distance_from_center_52_5mm = h/20
        height_offset_from_center = h/2.5

        # 上記正方形の射影変換後の画像における中心座標を求める(pix)
        cx, cy = w/2, h/2 + height_offset_from_center
        target_coordinates = np.float32(
            [[cx, cy-distance_from_center_52_5mm],
             [cx, cy+distance_from_center_52_5mm],
             [cx-distance_from_center_52_5mm, cy],
             [cx+distance_from_center_52_5mm, cy]])
        trans_mat = cv2.getPerspectiveTransform(
            frame_coordinates, target_coordinates)
        return trans_mat, distance_from_center_52_5mm, height_offset_from_center
