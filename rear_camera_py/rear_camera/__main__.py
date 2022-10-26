import argparse

from rear_camera.calibrator import Calibrator
from rear_camera.camera_interface import CameraInterface
from rear_camera.line_angle_calculator import LineAngleCalculator

parser = argparse.ArgumentParser(description="回頭補正用角度算出プログラム")
parser.add_argument("--camera-num", type=int, default=0,
                    help="カメラID")
parser.add_argument("--calibrate", action="store_true",
                    help="キャリブレーションを行う場合指定するフラグ")
parser.add_argument("--debug", action="store_true",
                    help="デバッグを行う場合指定するフラグ")
args = parser.parse_args()


camera = CameraInterface(args.camera_num)

if args.calibrate:
    calibrator = Calibrator(camera)
    calibrator.calibrate()
    print("Calibrated")
else:
    lac = LineAngleCalculator(camera, debug=args.debug)
    print(lac.calc_yaw_angle(999))
