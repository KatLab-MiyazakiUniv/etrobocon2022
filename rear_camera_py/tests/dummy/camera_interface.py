import os
from typing import Union
import cv2
import numpy as np


class CameraInterface:
    def __init__(self, fname: str = "") -> None:
        self.__fname = fname

    def capture_image(self) -> Union[np.ndarray, None]:
        if not os.path.exists(self.__fname):
            return None
        img = cv2.imread(self.__fname)
        return img
