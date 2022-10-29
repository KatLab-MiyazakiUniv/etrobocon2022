"""黒抽出モジュール.

リアカメラから取得した画像を黒白の2値画像に変換する。
@author kodama0720
"""
import cv2
from typing import List
import numpy as np
import time


class BlackExtractor:
    """画像の色変換クラス.

    Attributes:
        __BGR_COLOR(ndarray): RGB値(白)
        __LOWER(ndarray): HSV閾値下限(白)
        __UPPER(ndarray): HSV閾値上限(白)
    """

    __WHITE = np.array([255, 255, 255])
    __LOWER = np.array([0, 0, 80])
    __UPPER = np.array([180, 245, 255])

    def extract_black(self, rear_camera_img: cv2.Mat) -> List[int]:
        """画像から黒線を抽出する関数.

        Args:
            rear_camera_img (cv2.Mat): リアカメラ画像

        Returns:
            2値変換した画像データ: List[int]
        """
        y_size = rear_camera_img.shape[0]  # 入力画像の縦サイズ
        x_size = rear_camera_img.shape[1]  # 入力画像の横サイズ
        color_size = rear_camera_img.shape[2]  # RGBの3次元
        # BGR色空間からHSV色空間への変換
        hsv = cv2.cvtColor(rear_camera_img, cv2.COLOR_BGR2HSV)
        # 処理結果を保持する配列を宣言(色を黒で初期化)
        result = np.zeros((x_size*y_size, color_size), np.uint8)

        # 元画像を一次元の配列に変形
        hsv = hsv.reshape(result.shape)

        # 条件を満たすindexを取得
        index = np.where(np.all(BlackExtractor.__LOWER <= hsv, axis=1)
                         & np.all(hsv <= BlackExtractor.__UPPER, axis=1))

        # 2値画像に変換
        result[index] = BlackExtractor.__WHITE

        # 元の形状に変形
        result = result.reshape(rear_camera_img.shape)

        return result


if __name__ == "__main__":
    read_path = "rear_camera1.png"
    save_path = "binary_" + read_path
    rear_camera_img = cv2.imread(read_path)
    # インスタンス化
    black_extractor = BlackExtractor()

    # 処理前の時刻
    t1 = time.time()
    # 2値変換
    result = black_extractor.extract_black(rear_camera_img)
    # 処理後の時刻
    t2 = time.time()
    # 経過時間を表示
    elapsed_time = t2-t1
    print(f"経過時間：{elapsed_time}")

    # 2値画像を保存
    cv2.imwrite(save_path, result)

    print("black_extractor 終了")
