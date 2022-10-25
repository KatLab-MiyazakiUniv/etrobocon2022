import argparse

from rear_camera.calibrator import Calibrator
from rear_camera.line_angle_calculator import LineAngleCalculator

parser = argparse.ArgumentParser(description="回頭補正用角度算出プログラム")
parser.add_argument("--calibrate", action="store_true",
                    help="キャリブレーションを行う場合指定するフラグ")
args = parser.parse_args()


if args.calibrate:
    calibrator = Calibrator()
    calibrator.calibrate()
    print("Calibrated")
else:
    lac = LineAngleCalculator()
    print(lac.calc_yaw_angle())
