"""Arucoマーカを用いたリアカメラのキャリブレーションを行うモジュール.

@author Takahiro55555
"""

import json
from typing import Tuple, List

import cv2
from cv2 import aruco
import numpy as np

from rear_camera.camera_interface import CameraInterface


class Calibrator:
    """リアカメラのキャリブレーションを行うクラス."""

    def __init__(
        self, camera_interface: CameraInterface,
        trans_mat_file: str = "rear_camera_param.npy",
        distance_file: str = "rear_camera_distance_param.json"
    ) -> None:
        """コンストラクタ.

        Args:
            camera_interface (CameraInterface, optional): リアカメラのCameraInterfaceインスタンス.
                                                          Defaults to CameraInterface().
            trans_mat_file (str, optional): 射影変換用パラメータファイル名. Defaults to "rear_camera_param.npy".
            distance_file (str, optional): 射影変換後の画像座標と走行体の中心からの距離等の関係を保持するパラメータファイル名.
                                           Defaults to "rear_camera_distance_param.json".
        """
        self.__camera_interface = camera_interface
        self.__aruco_dictionary = aruco.getPredefinedDictionary(
            aruco.DICT_4X4_50)
        self.__trans_mat_file = trans_mat_file
        self.__distance_file = distance_file

    def _calc_param(self, img: np.ndarray) -> Tuple[np.ndarray, float, float]:
        """各種パラメータを計算する関数.

        Args:
            img (np.ndarray): キャリブレーション用画像.

        Raises:
            RuntimeError: キャリブレーション用のArUcoマーカを検出できなかった場合に発生.

        Returns:
            Tuple[np.ndarray, float, float]: 各種パラメータ(射影変換パラメータ、pixとmmの縮尺パラメータ、
                                                画像中心点と4つのキャリブレーション用ArUcoマーカで結んだ中心点の距離[pix]).
        """
        # 各マーカーの角4点を格納した二次元配列(corners)と、検出したマーカーIDを格納した1次元配列(ids)を取得
        # idsマーカIDの並びはcornersのに格納されているマーカの座標の並びと一致する
        corners, ids, _ = aruco.detectMarkers(
            img, self.__aruco_dictionary)
        if ids is None:
            raise RuntimeError("Could not find markers.")

        h, w = img.shape[:2]
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

    def calibrate(self):
        """キャリブレーションを行い、結果をパラメータファイルとして出力する関数.

        Raises:
            RuntimeError: リアカメラの画像を取得できなかった際に発生する.
        """
        img = self.__camera_interface.capture_image()
        if img is None:
            raise RuntimeError("Could not capture camera image.")
        trans_mat, distance_from_center_52_5mm, height_offset_from_center = self._calc_param(
            img)
        np.save(self.__trans_mat_file, trans_mat)
        distance_data = {
            "distance_from_center_52_5mm": distance_from_center_52_5mm,
            "height_offset_from_center": height_offset_from_center
        }
        with open(self.__distance_file, mode="w") as fp:
            json.dump(distance_data, fp)

    def __get_marker_mean(
        self,
        ids: np.ndarray,
        corners: List[np.ndarray],
        target_id: int
    ) -> Tuple[float, float]:
        """指定したIDのArUcoマーカの中心座標を取得する関数.

        Args:
            ids (np.ndarray): cornersのデータに対応するArUcoマーカのID.
            corners (List[np.ndarray]): 検出したArUcoマーカの角座標.
            target_id (int): ArUcoマーカのID.

        Raises:
            ValueError: 指定したIDのArUcoマーカが存在しなかった場合に発生.

        Returns:
            Tuple[float, float]: ArUcoマーカの中心座標[pix].
        """
        for i, id in enumerate(ids):
            # マーカーのインデックス検索
            if (id[0] == target_id):
                v = np.mean(corners[i][0], axis=0)  # マーカーの四隅の座標から中心の座標を取得する
                return v[0], v[1]
        raise ValueError("Index(%d) not found")
