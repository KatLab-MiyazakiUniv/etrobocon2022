"""LineAngleCalculatorクラスのテストを記述するモジュール.

Calibratorクラスのパラメータファイルが正常に生成されているかのテストも一部兼ねている.

@author: Takahiro55555
"""

import os
import unittest

from rear_camera.calibrator import Calibrator
from tests.dummy.camera_interface import CameraInterface
from rear_camera.line_angle_calculator import LineAngleCalculator


class TestCalibrator(unittest.TestCase):
    def setUp(self) -> None:
        """テストの下準備を行う関数."""
        # キャリブレーションを行い、パラメータファイルを生成する
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
        """テストの後始末を行う関数."""
        if os.path.isfile(self.__tmp_trans_mat_file):
            os.remove(self.__tmp_trans_mat_file)
        if os.path.isfile(self.__tmp_distance_file):
            os.remove(self.__tmp_distance_file)

    def test_calc_yaw_angle(self):
        """角度算出のテスト."""
        line_angle_calculator = LineAngleCalculator(
            self.__normal_camera_interface, self.__tmp_trans_mat_file, self.__tmp_distance_file, debug=True)
        expected = -43
        actual = line_angle_calculator.calc_yaw_angle()
        # 期待値と実際の値がdelta以下であることを検証
        self.assertAlmostEqual(expected, actual, delta=1.0)

    def test_mm_to_pix_2_pix_to_mm(self):
        """pixからmmへの変換が行えるかを検証する."""
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
        """mmからpixへの変換が行えるかを検証する."""
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
