from typing import Union
import cv2
import numpy as np


class CameraInterface:
    def __init__(self, camera_id: int = 0) -> None:
        self.__camera_id = camera_id

    def capture_image(self) -> Union[np.ndarray, None]:
        import subprocess
        fname = 'input.png'
        cmd = ["/usr/bin/libcamera-still", "-n", "--encoding",  "png", "--width", "3280", "--height", "2464", "-o", fname]
        res = subprocess.call(cmd)
        return cv2.imread(fname)
