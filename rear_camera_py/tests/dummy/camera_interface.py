"""カメラインターフェースのダミーモジュール.

@author Takahiro55555
"""

import os
from typing import Union
import cv2
import numpy as np


class CameraInterface:
    """カメラインターフェースのダミークラス."""

    def __init__(self, fname: str = "") -> None:
        """コンストラクタ.

        Args:
            fname (str, optional): 撮影用関数を実行した際に取得したい画像ファイル名を指定する. Defaults to "".
        """
        self.__fname = fname

    def capture_image(self) -> Union[np.ndarray, None]:
        """ダミーのカメラ画像を取得する関数.

        Returns:
            Union[np.ndarray, None]: コンストラクタで指定した画像ファイルのデータ.
        """
        if not os.path.exists(self.__fname):
            return None
        img = cv2.imread(self.__fname)
        return img
