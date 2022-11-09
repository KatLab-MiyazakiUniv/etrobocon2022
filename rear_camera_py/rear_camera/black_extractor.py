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
        # 2値変換
        binary_img = 255 - cv2.inRange(hsv, black_lower, black_upper)
        # 以下、テスト用
        binary_img = np.array([binary_img.T[:,:],binary_img.T[:,:],binary_img.T[:,:]]).T
        test_img = im_v = cv2.vconcat([binary_img, img])
        return test_img
        # 以上、テスト用
        return binary_img

for i in range(1,21):
    filename = "course_img (%d).png" % i
    img = cv2.imread("test_image/%s" % filename)
    binary_img = BlackExtractor.extract_black(img)
    cv2.imwrite("result_image/%s" % filename, binary_img)

for i in range(1,34):
    filename = "trans_image (%d).png" % i
    img = cv2.imread("test_image/%s" % filename)
    binary_img = BlackExtractor.extract_black(img)
    cv2.imwrite("result_image/%s" % filename, binary_img)