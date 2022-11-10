"""黒抽出モジュール.

リアカメラから取得した画像を黒白の2値画像データに変換する。
@author kodama0720
"""
import cv2
import numpy as np


class BlackExtractor:
    """画像の色変換クラス."""

    @staticmethod
    def extract_black(rear_camera_img: np.ndarray) -> np.ndarray:
        """画像から黒線を抽出する関数.

        Args:
            rear_camera_img (np.ndarray): リアカメラ画像

        Returns:
            np.ndarray: 2値変換した画像データ
        """
        black_lower = np.array([0, 0, 0])  # 黒と識別するための最低HSV値
        black_upper = np.array([180, 100, 60])  # 黒と識別するための最高HSV値

        # BGR色空間からHSV色空間への変換
        hsv = cv2.cvtColor(rear_camera_img, cv2.COLOR_BGR2HSV)
        # 2値変換（条件を満たす画素が255となるため、255から引くことで反転させる）
        binary_img = 255 - cv2.inRange(hsv, black_lower, black_upper)
        return binary_img
