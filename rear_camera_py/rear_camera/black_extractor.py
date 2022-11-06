"""黒抽出モジュール.

リアカメラから取得した画像を黒白の2値画像データに変換する。
@author kodama0720
"""
import cv2
from typing import List
import numpy as np


class BlackExtractor:
    """画像の色変換クラス."""

    @staticmethod
    def extract_black(rear_camera_img: np.ndarray) -> np.ndarray:
        """画像から黒線を抽出する関数.

        Args:
            rear_camera_img (np.ndarray): リアカメラ画像

        Returns:
            2値変換した画像データ: List[int]
        """
        lower = np.array([0, 0, 80])  # 白と識別するための最低HSV値
        upper = np.array([180, 255, 255])  # 白と識別するための最高HSV値

        # BGR色空間からHSV色空間への変換
        hsv = cv2.cvtColor(rear_camera_img, cv2.COLOR_BGR2HSV)
        # 2値変換
        binary_img = cv2.inRange(hsv, lower, upper)

        return binary_img
