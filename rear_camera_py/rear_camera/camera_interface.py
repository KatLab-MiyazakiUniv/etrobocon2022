from typing import Union

import cv2
from picamera2 import Picamera2
import numpy as np

class CameraInterface:
    def __init__(self, camera_id: int = 0) -> None:
        """カメラインターフェースのコンストラクタ.

        WARNING:
            ここでカメラデバイスを初期化すると、
            デフォルト引数は定義時評価というPythonの仕様により、
            カメラデバイスを同時に複数回初期化しようとしてエラーが発生する場合がある.
            これは、複数個所でCameraInterfaceをデフォルト引数に設定している場合に生じる.
        """
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
