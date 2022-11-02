"""BlackExtractorクラスのテストコードを記述するモジュール.

@author: kodama0720
"""

import unittest
import numpy as np
import cv2
import os
from camera_system.black_extractor import BlackExtractor


class TestBlackExtractor(unittest.TestCase):
    def test_black_extractor(self):
        be = BlackExtractor()
        read_path = os.path.dirname(os.path.realpath(__file__)) + "/test_data/test_rear_image.png"
        save_path = os.path.dirname(os.path.realpath(__file__)) + "/test_data/test_binary_image.png"
        img = cv2.imread(read_path)

        # black_extractorモジュールのテスト(画像が生成されているか)
        if os.path.exists(save_path):  # テスト前に画像があったら消去
            os.remove(save_path)
        result = be.extract_black(img)
        # 2値画像を保存
        cv2.imwrite(save_path, result)
        expected_exist = True
        actual_exist = os.path.exists(save_path)  # 画像が生成されているか確認(bool)
        self.assertEqual(expected_exist, actual_exist)
