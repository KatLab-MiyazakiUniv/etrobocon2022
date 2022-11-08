"""mainモジュール.

プロジェクトルートで、以下のコマンドを実行すると最初に呼び出されるファイル
> python -m rear_camera

必要最低限のコードのみを記述するようにする
@author: Takahiro55555
"""
import argparse

from rear_camera.angle_server import AngleServer
from rear_camera.calibrator import Calibrator
from rear_camera.camera_interface import CameraInterface
from rear_camera.line_angle_calculator import LineAngleCalculator

parser = argparse.ArgumentParser(description="回頭補正用角度算出プログラム")
parser.add_argument("--min-area-size", type=int, default=999,
                    help="この値より小さな面積の黒線を無視する")
parser.add_argument("--camera-num", type=int, default=0,
                    help="カメラID")
parser.add_argument("--calibrate", action="store_true",
                    help="キャリブレーションを行う場合指定するフラグ")
parser.add_argument("--debug", action="store_false",
                    help="デバッグを行う場合指定するフラグ")
parser.add_argument("--server", action="store_false",
                    help="サーバモードを利用する場合指定するフラグ")
parser.add_argument("--server-ip", type=str, default="127.0.0.1",
                    help="サーバのIPアドレス(同一ホスト内のプロセス間通信の場合、デフォルト値でOK).")
parser.add_argument("--server-port", type=int, default=10338,
                    help="サーバのListenポート")


args = parser.parse_args()


camera = CameraInterface(args.camera_num)
camera.start_camera()

if args.calibrate:
    calibrator = Calibrator(camera)
    calibrator.calibrate()
    print("Calibrated")
elif args.server:
    lac = LineAngleCalculator(camera, debug=args.debug)
    angle_server = AngleServer(
        server_ip=args.server_ip,
        server_port=args.server_port,
        listen_num=127,
        buf_size=1024,
        debug=args.debug
    )
    angle_server.add_command('angle', lambda _: str(lac.calc_yaw_angle(args.min_area_size)))
else:
    lac = LineAngleCalculator(camera, debug=args.debug)
    print(lac.calc_yaw_angle(999))
