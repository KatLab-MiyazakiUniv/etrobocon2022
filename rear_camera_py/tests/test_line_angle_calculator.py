
import os
import unittest

from rear_camera.calibrator import Calibrator
from tests.dummy.camera_interface import CameraInterface
from rear_camera.line_angle_calculator import LineAngleCalculator


class TestCalibrator(unittest.TestCase):
    def setUp(self) -> None:
        # キャリブレーションを行う
        calibration_fname = "tests/test_data/group-00-calibration-image-normal.png"
        self.__calibration_camera_interface = CameraInterface(
            calibration_fname)
        self.__tmp_trans_mat_file = "tmp_rear_camera_param.npy"
        self.__tmp_distance_file = "tmp_rear_camera_distance_param.json"
        calibrator = Calibrator(
            self.__calibration_camera_interface, self.__tmp_trans_mat_file, self.__tmp_distance_file)
        calibrator.calibrate()

        normal_fname = "tests/test_data/group-00-game-image-normal-00.png"
        self.__normal_camera_interface = CameraInterface(normal_fname)

    def doCleanups(self) -> None:
        """後始末用関数."""
        if os.path.isfile(self.__tmp_trans_mat_file):
            os.remove(self.__tmp_trans_mat_file)
        if os.path.isfile(self.__tmp_distance_file):
            os.remove(self.__tmp_distance_file)

    def test_calc_yaw_angle(self):
        # テスト
        line_angle_calculator = LineAngleCalculator(
            self.__normal_camera_interface, self.__tmp_trans_mat_file, self.__tmp_distance_file, debug=True)
        expected = 45
        actual = line_angle_calculator.calc_yaw_angle()
        self.assertEqual(expected, actual)
        contours, hierarchy = cv2.findContours(img_bin, 3, 1)

    def calc_contour_area_mm2(self):
        h, w = 100, 100
        img = np.zeros((h, w, 1), np.uint8)
        img[0:1, :] = 255  # 上辺を255にする
        img[:, 0:1] = 255  # 左辺を255にする
        img[:, w-1:w] = 255  # 右辺を255にする
        img[h-1:h, :] = 255  # 右辺を255にする

    def test_mm_to_pix_2_pix_to_mm(self):
        line_angle_calculator = LineAngleCalculator(
            self.__normal_camera_interface, self.__tmp_trans_mat_file, self.__tmp_distance_file, debug=True)
        original = 10
        pix = line_angle_calculator.mm_to_pix(original)
        mm = line_angle_calculator.pix_to_mm(pix)
        self.assertEqual(original, mm)

        original = -100
        pix = line_angle_calculator.mm_to_pix(original)
        mm = line_angle_calculator.pix_to_mm(pix)
        self.assertAlmostEqual(original, mm)

        original = 948723894
        pix = line_angle_calculator.mm_to_pix(original)
        mm = line_angle_calculator.pix_to_mm(pix)
        self.assertAlmostEqual(original, mm)

    def test_pix_to_mm_2_mm_to_pix(self):
        line_angle_calculator = LineAngleCalculator(
            self.__normal_camera_interface, self.__tmp_trans_mat_file, self.__tmp_distance_file, debug=True)
        original = 10
        mm = line_angle_calculator.pix_to_mm(original)
        pix = line_angle_calculator.mm_to_pix(mm)
        self.assertAlmostEqual(original, pix)

        original = -100
        mm = line_angle_calculator.pix_to_mm(original)
        pix = line_angle_calculator.mm_to_pix(mm)
        self.assertAlmostEqual(original, pix)

        original = 93245837532
        mm = line_angle_calculator.pix_to_mm(original)
        pix = line_angle_calculator.mm_to_pix(mm)
        self.assertAlmostEqual(original, pix)
