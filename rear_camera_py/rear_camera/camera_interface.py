from typing import Union

import cv2
from picamera2 import Picamera2
import numpy as np

class CameraInterface:
    def __init__(self, camera_id: int = 0) -> None:
        self.__camera_id = camera_id
        self.__picam2 = None

    @property
    def picam2(self) -> None:
        pass

    @picam2.getter
    def picam2(self) -> Picamera2:
        if self.__picam2 is None:
            picam2 = Picamera2(camera_num=self.__camera_id)
            picam2.configure(picam2.create_preview_configuration(main={"format": 'XRGB8888', "size": (1640, 1232)}))
            picam2.start()
            self.__picam2 = picam2
        return self.__picam2

    def capture_image(self) -> Union[np.ndarray, None]:
        return self.picam2.capture_array()
