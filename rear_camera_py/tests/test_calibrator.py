import os
import unittest

import numpy as np

from rear_camera.calibrator import Calibrator
from tests.dummy.camera_interface import CameraInterface


class TestCalibrator(unittest.TestCase):
    def test_calc_param_normal(self):
        fname = "tests/test_data/group-00-calibration-image-normal.png"
        img = CameraInterface(fname).capture_image()
        calibrator = Calibrator()
        trans_mat, distance_from_center_52_5mm, height_offset_from_center = calibrator.calc_param(
            img)
        self.assertEqual(type(trans_mat), np.ndarray)
        self.assertEqual(type(distance_from_center_52_5mm), float)
        self.assertEqual(type(height_offset_from_center), float)

    def test_calc_param_could_not_find_markers(self):
        fname = "tests/test_data/group-00-game-image-normal-00.png"
        img = CameraInterface(fname).capture_image()
        calibrator = Calibrator()
        with self.assertRaises(RuntimeError):
            calibrator.calc_param(img)

    def test_calibrate_normal(self):
        fname = "tests/test_data/group-00-calibration-image-normal.png"
        camera_interface = CameraInterface(fname)
        tmp_trans_mat_file = "tmp_rear_camera_param.npy"
        tmp_distance_file = "tmp_rear_camera_distance_param.json"
        if os.path.isfile(tmp_trans_mat_file):
            os.remove(tmp_trans_mat_file)
        if os.path.isfile(tmp_distance_file):
            os.remove(tmp_distance_file)
        calibrator = Calibrator(
            camera_interface, tmp_trans_mat_file, tmp_distance_file)
        calibrator.calibrate()
        self.assertTrue(os.path.isfile(tmp_trans_mat_file))
        self.assertTrue(os.path.isfile(tmp_distance_file))
        if os.path.isfile(tmp_trans_mat_file):
            os.remove(tmp_trans_mat_file)
        if os.path.isfile(tmp_distance_file):
            os.remove(tmp_distance_file)
