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
    def extract_black(rear_camera_img: cv2.Mat) -> List[int]:
        """画像から黒線を抽出する関数.

        Args:
            rear_camera_img (cv2.Mat): リアカメラ画像

        Returns:
            2値変換した画像データ: List[int]
        """
        MIN_WHITE_VALUE = 80  # 白と識別するための最低明度
        lower = np.array([0, 0, MIN_WHITE_VALUE])
        upper = np.array([180, 255, 255])

        # BGR色空間からHSV色空間への変換
        hsv = cv2.cvtColor(rear_camera_img, cv2.COLOR_BGR2HSV)
        # 2値変換
        binary_img = cv2.inRange(hsv, lower, upper)

        return binary_img


if __name__ == "__main__":
    read_path = "rear_camera1.png"
    save_path = "binary_" + read_path
    rear_camera_img = cv2.imread(read_path)

    # 2値変換
    result = BlackExtractor.extract_black(rear_camera_img)
    # 2値画像を保存
    cv2.imwrite(save_path, result)

    print("black_extractor 終了")
