"""カメラインターフェースモジュール.

CameraInterfaceインスタンスを利用することでカメラ画像を取得することができる.
@author Takahiro55555
"""

from typing import Tuple, Union

from picamera2 import Picamera2
import numpy as np


class CameraInterface:
    """カメラインターフェースクラス."""

    def __init__(
        self,
        camera_id: int = 0,
        data_format: str = 'RGB888',
        size: Tuple[int, int] = (1640, 1232)
    ) -> None:
        """カメラインターフェースのコンストラクタ.

        WARNING: キャリブレーション時と同じ解像度に設定しないとバグる.

        WARNING:
            ここでカメラデバイスを初期化すると、
            デフォルト引数は定義時評価というPythonの仕様により、
            カメラデバイスを同時に複数回初期化しようとしてエラーが発生する場合がある.
            これは、複数個所でCameraInterfaceをデフォルト引数に設定している場合、
            もしくは、1箇所デフォルト引数に設定した上で、
            さらに処理中にCameraInterfaceをインスタンス化した際に発生する可能性がある.
        """
        self.__camera_id = camera_id
        self.__format = data_format
        self.__size = size
        self.__picam2 = None

    def start_camera(self) -> None:
        """Picamera2インスタンスの初期化を行う."""
        if self.__picam2 is None:
            picam2 = Picamera2(camera_num=self.__camera_id)
            conf = picam2.create_preview_configuration(
                main={"format": self.__format, "size": self.__size})
            picam2.configure(conf)
            picam2.start()
            self.__picam2 = picam2

    def capture_image(self) -> Union[np.ndarray, None]:
        """カメラ画像を取得する関数.

        Returns:
            Union[np.ndarray, None]: カメラ画像データ
        """
        return self.__picam2.capture_array()
