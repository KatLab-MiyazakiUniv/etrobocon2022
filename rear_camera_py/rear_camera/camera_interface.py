from typing import Union
import cv2
import numpy as np


class CameraInterface:
    def __init__(self, camera_id: int = 0) -> None:
        self.__camera_id = camera_id

    def capture_image(self) -> Union[np.ndarray, None]:
        cap = cv2.VideoCapture(self.__camera_id)
        ret, frame = cap.read()
        if not ret:
            return None
        return frame
