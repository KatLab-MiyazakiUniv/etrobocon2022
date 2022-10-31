"""コースの直線に対する機体の角度算出するモジュール."""

import json
import os
import time
from typing import Tuple, Union

import cv2
import numpy as np

from rear_camera.camera_interface import CameraInterface


class LineAngleCalculator:
    """コースの直線に対する機体の角度算出するクラス."""

    def __init__(
        self,
        camera_interface: CameraInterface = CameraInterface(),
        trans_mat_file: str = "rear_camera_param.npy",
        distance_file: str = "rear_camera_distance_param.json",
        debug: bool = False,
        debug_dir="debug"
    ) -> None:
        """コンストラクタ.

        Args:
            camera_interface (CameraInterface, optional): リアカメラ画像を取得するためのCameraInterfaceインスタンス.
                                                          Defaults to CameraInterface().
            trans_mat_file (str, optional): 射影変換用パラメータファイル名. Defaults to "rear_camera_param.npy".
            distance_file (str, optional): 射影変換後の画像座標と走行体の中心からの距離等の関係を保持するパラメータファイル名.
                                           Defaults to "rear_camera_distance_param.json".
            debug (bool, optional): Trueに設定するとデバッグ用の画像ファイルが生成される. Defaults to False.
            debug_dir (str, optional): デバッグ用の画像ファイルを生成するディレクトリ(存在しない場合は自動で生成される).
                                       Defaults to "debug".

        Raises:
            FileNotFoundError: 各種パラメータファイルが見つからない場合に発生.
            KeyError: 射影変換後の画像座標と走行体の中心からの距離等の関係を保持するパラメータファイルのデータが一部でも欠損している場合に発生.
        """
        self.__camera_interface = camera_interface
        if not os.path.isfile(trans_mat_file):
            raise FileNotFoundError("file name: '%s'" % trans_mat_file)
        if not os.path.isfile(distance_file):
            raise FileNotFoundError("file name: '%s'" % distance_file)
        self.__trans_mat = np.load(trans_mat_file)

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
        with open(distance_file) as fp:
            distance_data = json.load(fp)
        key = "distance_from_center_52_5mm"
        if key not in distance_data:
            raise KeyError("key not found: '%s', file: %s" %
                           (key, distance_file))
        self.__distance_from_center_52_5mm = distance_data[key]
        key = "height_offset_from_center"
        if key not in distance_data:
            raise KeyError("key not found: '%s', file: %s" %
                           (key, distance_file))
        self.__height_offset_from_center = distance_data[key]
        self.__debug = debug
        if not os.path.exists(debug_dir):
            os.makedirs(debug_dir)
        self.__debug_dir = debug_dir

    def calc_yaw_angle(
        self,
        contours_area_size_min_threshold_mm2: int = 9999,
        debug_img_fname_prefix: str = "angle"
    ) -> Union[float, None]:
        """検出した直線と機体の中心線とのなす角を算出する.

        Args:
            contours_area_size_min_threshold_mm2 (int, optional): ノイズとして排除する検出した直線の面積の閾値.
                                                                  Defaults to 9999.
            debug_img_fname_prefix (str, optional): デバッグ用画像の接頭辞. Defaults to "angle".

        Returns:
            Union[float, None]: 検出した直線と機体の中心線とのなす角、直線を検出できなかった場合は`None`を返す.
        """
        img = self.__camera_interface.capture_image()
        if img is None:
            return None

        if self.__debug:
            debug_time = time.time()
            img_fname = "%s_%f_captured.png" % (
                debug_img_fname_prefix, debug_time)
            debug_img_path = os.path.join(self.__debug_dir, img_fname)
            cv2.imwrite(debug_img_path, img)
        img_transformed = self.get_transformed_image(img)
        img_gray = cv2.cvtColor(img_transformed, cv2.COLOR_BGR2GRAY)
        img_gray[0:1, :] = 255
        img_bin = cv2.threshold(img_gray, 60, 255, cv2.THRESH_BINARY)[1]
        contours, hierarchy = cv2.findContours(img_bin, 3, 1)
        max_area_threshold = cv2.contourArea(
            max(contours, key=lambda x: cv2.contourArea(x)))  # 画像の外周を除去
        filtered_contours = list(
            filter(lambda x: cv2.contourArea(x) >= contours_area_size_min_threshold_mm2, contours))
        filtered_contours = list(filter(lambda x: cv2.contourArea(
            x) < max_area_threshold, filtered_contours))

        if len(filtered_contours) == 0:
            return None

        h, w = img.shape[:2]
        filtered_contours_sorted = sorted(
            filtered_contours, key=lambda x: self.__calc_contour_score(x, h, w))

        cnt = filtered_contours_sorted[-1]
        h, w = img_transformed.shape[:2]
        vx, vy, x, y = cv2.fitLine(
            cnt, cv2.DIST_L2, 0, 0.01, 0.01)  # 検出したコースの黒線を直線で近似
        # unit vector in the same direction as the x axis
        y_axis = np.array([0, 1])
        # unit vector in the same direction as your line
        your_line = np.array([vx, vy])
        dot_product = np.dot(y_axis, your_line)
        angle_2_y = np.arccos(dot_product) * 180 / np.pi
        if angle_2_y > 90:
            angle_2_y -= 180
        if self.__debug:
            debug_img = self.draw_detected_lines_on_the_image(
                img_transformed, cnt, angle_2_y)
            img_fname = "%s_%f_detected.png" % (
                debug_img_fname_prefix, debug_time)
            debug_img_path = os.path.join(self.__debug_dir, img_fname)
            cv2.imwrite(debug_img_path, debug_img)
        return float(angle_2_y)

    # def calc_contour_area_mm2(self, contour: np.ndarray, img_h: int, img_w: int) -> float:
    #     tmp_img_for_calc_contour_area_mm2 = np.zeros(
    #         (img_h, img_w, 1), np.uint8)
    #     tmp_img_for_calc_contour_area_mm2 = cv2.drawContours(
    #         tmp_img_for_calc_contour_area_mm2, [contour], 0, (1), -1)
    #     contour_area_pix = np.sum(tmp_img_for_calc_contour_area_mm2)

    def __calc_contour_score(self, contour: np.ndarray, img_h: int, img_w: int) -> float:
        """直線と機体のなす角を算出する際に採用する直線を決定するためのスコアを算出する関数.

        現状は、直線の中心と機体の中心間の距離を用いている.

        Args:
            contour (np.ndarray): 検出した直線の輪郭データ
            img_h (int): 画像の縦幅[pix]
            img_w (int): 画像の横幅[pix]

        Returns:
            float: スコア
        """
        _, y_mm = self.calc_contour_runner_base_center_mm(
            contour, img_h, img_w)
        return y_mm

    @staticmethod
    def calc_contour_center_pix(contour: np.ndarray) -> Tuple[float, float]:
        """検出した直線(の輪郭)の重心を算出する関数.

        NOTE:
            - [参考サイト](https://cvtech.cc/pycvmoment/)

        Args:
            contour (np.ndarray): 輪郭データ.

        Returns:
            Tuple[float, float]: 重心座標[pix]
        """
        mu = cv2.moments(contour)
        x, y = mu["m10"]/mu["m00"], mu["m01"]/mu["m00"]
        return x, y

    def calc_contour_runner_base_center_mm(
        self,
        contour: np.ndarray,
        img_h: int,
        img_w: int
    ) -> Tuple[float, float]:
        """機体の中心を基準とした直線(の輪郭)の中心座標[mm]を算出する.

        Args:
            contour (np.ndarray): 検出した直線の輪郭.
            img_h (int): 画像の縦幅[pix].
            img_w (int): 画像の横幅[pix].

        Returns:
            Tuple[float, float]: 機体の中心を基準とした直線(の輪郭)の中心座標(x, y)[mm].
        """
        px, py = self.calc_contour_center_pix(contour)
        x_mm, y_mm = self.image_base_coordinate_to_runner_base_coordinate_mm(
            px, py, img_h, img_w)
        return x_mm, y_mm

    def get_transformed_image(self, img: np.ndarray, borderValue=(255, 255, 255)) -> np.ndarray:
        """射影変換を行った画像を取得する.

        Args:
            img (np.ndarray): 射影変換前の画像.
            borderValue (tuple, optional): 射影変換後の画像における余白部分の色. Defaults to (255, 255, 255).

        Returns:
            np.ndarray: 射影変換後の画像.
        """
        return cv2.warpPerspective(
            img, self.__trans_mat, (img.shape[1], img.shape[0]), borderValue=borderValue)

    def pix_to_mm(self, pix: Union[int, float]) -> float:
        """pixをmmに変換する.

        Args:
            pix (Union[int, float]): 変換したい値[pix]

        Returns:
            float: 変換結果[mm]
        """
        return pix * 52.5 / self.__distance_from_center_52_5mm

    def mm_to_pix(self, mm: Union[int, float]) -> float:
        """mmをpixに変換する.

        Args:
            mm (Union[int, float]): 変換したい値[mm]

        Returns:
            float: 変換結果[mm]
        """
        return mm * self.__distance_from_center_52_5mm / 52.5

    def image_base_coordinate_to_runner_base_coordinate_mm(
        self,
        img_x: Union[int, float],
        img_y: Union[int, float],
        img_h: int,
        img_w: int
    ) -> Tuple[float, float]:
        """画像上の座標を機体の中心を原点とした座標に変換する.

        Args:
            img_x (Union[int, float]): 画像上のX座標[pix].
            img_y (Union[int, float]): 画像上のY座標[pix].
            img_h (int): 画像の縦幅[pix].
            img_w (int): 画像の横幅[pix].

        Returns:
            Tuple[float, float]: 変換後の座標(x, y)[mm].
        """
        distance_between_aruco_markers_center_and_runner_center_mm = 312.5
        img_x_axis_and_runner_x_axis_distance_mm = (
            self.pix_to_mm(self.__height_offset_from_center) +
            distance_between_aruco_markers_center_and_runner_center_mm
        )
        img_h_mm = self.pix_to_mm(img_h)
        img_w_mm = self.pix_to_mm(img_w)
        runner_base_x_mm = self.pix_to_mm(img_x) - img_w_mm/2
        runner_base_y_mm = img_x_axis_and_runner_x_axis_distance_mm - \
            (img_h_mm - self.pix_to_mm(img_y))
        return runner_base_x_mm, runner_base_y_mm

    def runner_base_coordinate_to_image_base_coordinate_pix(
        self,
        rx: Union[int, float],
        ry: Union[int, float],
        img_h: int,
        img_w: int
    ) -> Tuple[int, int]:
        """機体の中心を原点とした座標に変換する.

        Args:
            rx (Union[int, float]): 走行体の中心を原点としたX座標[mm].
            ry (Union[int, float]): 走行体の中心を原点としたY座標[mm].
            img_h (int): 画像の縦幅[pix].
            img_w (int): 画像の横幅[pix].

        Returns:
            Tuple[int, int]: 変換後の座標(x, y)[pix].
        """
        pix_x = self.mm_to_pix(rx) + img_w/2
        pix_y = self.__height_offset_from_center + 312.5 - self.mm_to_pix(ry)
        return pix_x, pix_y

    def draw_detected_lines_on_the_image(
        self,
        img: np.ndarray,
        contour: np.ndarray,
        angle: float
    ) -> np.ndarray:
        """検出した直線及び、その直線と機体の中心線のなす角を直線の検出用いた画像へ描画するデバッグ用関数.

        Args:
            img (np.ndarray): 直線の検出に用いた画像データ.
            contour (np.ndarray): 検出した直線の輪郭データ.
            angle (float): 検出した直線と機体の中心線とのなす角.

        Returns:
            np.ndarray: 検出した直線及び、その直線と機体の中心線のなす角を描画した画像データ.
        """
        _, w = img.shape[:2]
        vx, vy, x, y = cv2.fitLine(contour, cv2.DIST_L2, 0, 0.01, 0.01)
        lefty = int((-x*vy/vx)+y)
        righty = int(((w-x)*vy/vx)+y)
        cv2.drawContours(img, [contour], -1, (255, 255, 0), 3)
        cv2.line(img, (w-1, righty), (0, lefty), (0, 0, 255), 2)
        tx, ty = int(x), int(y)
        cv2.putText(img, "%.2f" % angle, (tx, ty),
                    cv2.FONT_HERSHEY_COMPLEX, 1.5, (0, 255, 0), thickness=2)
        return img
