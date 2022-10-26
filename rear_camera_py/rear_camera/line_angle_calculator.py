
import json
import os
import time
from typing import Tuple, Union

import cv2
import numpy as np

from rear_camera.camera_interface import CameraInterface


class LineAngleCalculator:
    def __init__(
        self,
        camera_interface: CameraInterface = CameraInterface(),
        trans_mat_file: str = "rear_camera_param.npy",
        distance_file: str = "rear_camera_distance_param.json",
        debug: bool = False,
        debug_dir="debug"
    ) -> None:
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

    def calc_yaw_angle(self, contours_area_size_min_threshold_mm2: int = 9999, debug_img_fname_prefix: str = "angle") -> Union[float, None]:
        img = self.__camera_interface.capture_image()
        if img is None:
            return None
        return self.__detect_lines(img, contours_area_size_min_threshold_mm2, debug_img_fname_prefix)

    def __detect_lines(self, img: np.ndarray, contours_area_size_min_threshold_mm2, debug_img_fname_prefix) -> Union[float, None]:
        if self.__debug:
            debug_time = time.time()
            img_fname = "%s_%f_captured.png" % (debug_img_fname_prefix, debug_time)
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
            img_fname = "%s_%f_detected.png" % (debug_img_fname_prefix, debug_time)
            debug_img_path = os.path.join(self.__debug_dir, img_fname)
            cv2.imwrite(debug_img_path, debug_img)
        return float(angle_2_y)

    def calc_contour_area_mm2(self, contour: np.ndarray, img_h: int, img_w: int) -> float:
        tmp_img_for_calc_contour_area_mm2 = np.zeros(
            (img_h, img_w, 1), np.uint8)
        tmp_img_for_calc_contour_area_mm2 = cv2.drawContours(
            tmp_img_for_calc_contour_area_mm2, [contour], 0, (1), -1)
        contour_area_pix = np.sum(tmp_img_for_calc_contour_area_mm2)

    def __calc_contour_score(self, contour: np.ndarray, img_h: int, img_w: int) -> float:
        _, y_mm = self.calc_contour_runner_base_center_mm(
            contour, img_h, img_w)
        return y_mm

    @staticmethod
    def calc_contour_center_pix(contour: np.ndarray) -> Tuple[float, float]:
        mu = cv2.moments(contour)
        x, y = mu["m10"]/mu["m00"], mu["m01"]/mu["m00"]
        return x, y

    def calc_contour_runner_base_center_mm(self, contour: np.ndarray, img_h: int, img_w: int) -> Tuple[float, float]:
        px, py = self.calc_contour_center_pix(contour)
        x_mm, y_mm = self.image_base_coordinate_to_runner_base_coordinate_mm(
            px, py, img_h, img_w)
        return x_mm, y_mm

    def get_transformed_image(self, img: np.ndarray, borderValue=(255, 255, 255)) -> np.ndarray:
        return cv2.warpPerspective(
            img, self.__trans_mat, (img.shape[1], img.shape[0]), borderValue=borderValue)

    def pix_to_mm(self, pix: Union[int, float]) -> float:
        return pix * 52.5 / self.__distance_from_center_52_5mm

    def mm_to_pix(self, mm: Union[int, float]) -> float:
        return mm * self.__distance_from_center_52_5mm / 52.5

    def image_base_coordinate_to_runner_base_coordinate_mm(self, img_x: Union[int, float], img_y: Union[int, float], img_h: int, img_w: int) -> Tuple[float, float]:
        distance_between_aruco_markers_center_and_runner_center_mm = 312.5
        img_x_axis_and_runner_x_axis_distance_mm = (
            self.pix_to_mm(self.__height_offset_from_center) + distance_between_aruco_markers_center_and_runner_center_mm)
        img_h_mm = self.pix_to_mm(img_h)
        img_w_mm = self.pix_to_mm(img_w)
        runner_base_x_mm = self.pix_to_mm(img_x) - img_w_mm/2
        runner_base_y_mm = img_x_axis_and_runner_x_axis_distance_mm - \
            (img_h_mm - self.pix_to_mm(img_y))
        return runner_base_x_mm, runner_base_y_mm

    def runner_base_coordinate_to_image_base_coordinate_pix(self, rx: Union[int, float], ry: Union[int, float], img_h: int, img_w: int) -> Tuple[int, int]:
        pix_x = self.mm_to_pix(rx) + img_w/2
        pix_y = self.__height_offset_from_center + 312.5 - self.mm_to_pix(ry)
        return pix_x, pix_y

    def __calc_runner_base_contour_moment_mm(self, contour: np.ndarray, img_h: int, img_w) -> Tuple[float, float]:
        moment_x, moment_y = self.__calc_image_base_contour_moment_pix(contour)
        return self.image_base_coordinate_to_runner_base_coordinate_mm(moment_x, moment_y, img_h, img_w)

    def __calc_image_base_contour_moment_pix(self, contour: np.ndarray) -> Tuple[float, float]:
        moment = cv2.moments(contour)
        cx = moment['m10']/moment['m00']
        cy = moment['m01']/moment['m00']
        return cx, cy

    def draw_detected_lines_on_the_image(self, img: np.ndarray, contour: np.ndarray, angle: float) -> np.ndarray:
        h, w = img.shape[:2]
        vx, vy, x, y = cv2.fitLine(contour, cv2.DIST_L2, 0, 0.01, 0.01)
        lefty = int((-x*vy/vx)+y)
        righty = int(((w-x)*vy/vx)+y)
        cv2.drawContours(img, [contour], -1, (255, 255, 0), 3)
        cv2.line(img, (w-1, righty), (0, lefty), (0, 0, 255), 2)
        tx, ty = int(x), int(y)
        cv2.putText(img, "%.2f" % angle, (tx, ty),
                    cv2.FONT_HERSHEY_COMPLEX, 1.5, (0, 255, 0), thickness=2)
        return img
