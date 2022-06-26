/**
 * @file Rotation.cpp
 * @brief 回頭・ピボットターンする
 * @author sugaken0528
 */

#include "Rotation.h"

using namespace std;

Rotation::Rotation()
  : RADIUS(45.0), TREAD(140), ROTATE_MIN_PWM(40), PIVOT_FRONT_MIN_PWM(40), PIVOT_BACK_MIN_PWM(40)
{
}

//左回転
void Rotation::rotateLeft(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to LineTracer::run is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  const double _TREAD = TREAD - 8;  // 回頭距離の調整
  int leftSign = -1;
  int rightSign = 1;
  double targetDistance = M_PI * _TREAD * abs(angle) / 360;  //弧の長さ
  //目標距離（呼び出し時の走行距離 ± 指定された回転量に必要な距離）
  double targetLeftDistance
      = Mileage::calculateWheelMileage(measurer.getLeftCount()) + targetDistance * leftSign;
  double targetRightDistance
      = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance * rightSign;

  //両輪が目標距離に到達するまでループ
  while(leftSign != 0 || rightSign != 0) {
    // 残りの移動距離
    double diffLeftDistance
        = (targetLeftDistance - Mileage::calculateWheelMileage(measurer.getLeftCount())) * leftSign;
    double diffRightDistance
        = (targetRightDistance - Mileage::calculateWheelMileage(measurer.getRightCount()))
          * rightSign;

    // 目標距離に到達した場合
    if(diffLeftDistance <= 0) {
      leftSign = 0;
    }
    if(diffRightDistance <= 0) {
      rightSign = 0;
    }

    // PWM値 = 残りの走行距離/走行距離 * 指定PWM値(最小値 MIN_PWM)
    int leftPwm = (diffLeftDistance / targetDistance * pwm >= ROTATE_MIN_PWM)
                      ? diffLeftDistance / targetDistance * pwm
                      : ROTATE_MIN_PWM;
    int rightPwm = (diffRightDistance / targetDistance * pwm >= ROTATE_MIN_PWM)
                       ? diffRightDistance / targetDistance * pwm
                       : ROTATE_MIN_PWM;
    controller.setLeftMotorPwm(abs(leftPwm) * leftSign);
    controller.setRightMotorPwm(abs(rightPwm) * rightSign);

    controller.sleep();
  }

  //モータの停止
  controller.stopMotor();
}

//右回転
void Rotation::rotateRight(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to LineTracer::run is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  const double _TREAD = TREAD - 8;  // 回頭距離の調整
  int leftSign = 1;
  int rightSign = -1;
  double targetDistance = M_PI * _TREAD * abs(angle) / 360;  //弧の長さ
  //目標距離（呼び出し時の走行距離 ± 指定された回転量に必要な距離）
  double targetLeftDistance
      = Mileage::calculateWheelMileage(measurer.getLeftCount()) + targetDistance * leftSign;
  double targetRightDistance
      = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance * rightSign;

  //両輪が目標距離に到達するまでループ
  while(leftSign != 0 || rightSign != 0) {
    // 残りの移動距離
    double diffLeftDistance
        = (targetLeftDistance - Mileage::calculateWheelMileage(measurer.getLeftCount())) * leftSign;
    double diffRightDistance
        = (targetRightDistance - Mileage::calculateWheelMileage(measurer.getRightCount()))
          * rightSign;

    // 目標距離に到達した場合
    if(diffLeftDistance <= 0) {
      leftSign = 0;
    }
    if(diffRightDistance <= 0) {
      rightSign = 0;
    }

    // PWM値 = 残りの走行距離/走行距離 * 指定PWM値(最小値 MIN_PWM)
    int leftPwm = (diffLeftDistance / targetDistance * pwm >= ROTATE_MIN_PWM)
                      ? diffLeftDistance / targetDistance * pwm
                      : ROTATE_MIN_PWM;
    int rightPwm = (diffRightDistance / targetDistance * pwm >= ROTATE_MIN_PWM)
                       ? diffRightDistance / targetDistance * pwm
                       : ROTATE_MIN_PWM;
    controller.setLeftMotorPwm(abs(leftPwm) * leftSign);
    controller.setRightMotorPwm(abs(rightPwm) * rightSign);

    controller.sleep();
  }

  //モータの停止
  controller.stopMotor();
}

//設定された角度とPWM値で右タイヤを軸に前方へピボットターンする
void Rotation::turnForwardRightPivot(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to LineTracer::run is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  int leftPwm = pwm;
  int rightPwm = -1;

  controller.resetMotorCount();
  double motorCount = 0;
  double targetMotorCount = calculate(angle);

  while(motorCount <= targetMotorCount) {
    if(pwm == 0) break;

    double leftCountRate = 1 - (measurer.getLeftCount() / targetMotorCount);
    leftPwm = pwm * leftCountRate > PIVOT_FRONT_MIN_PWM ? (int)(pwm * leftCountRate)
                                                        : PIVOT_FRONT_MIN_PWM;

    controller.setLeftMotorPwm(leftPwm);
    controller.setRightMotorPwm(rightPwm);

    motorCount = (measurer.getLeftCount() + measurer.getRightCount()) / 2;

    controller.sleep();
  }

  controller.stopMotor();
}

//設定された角度とPWM値で右タイヤを軸に後方へピボットターンする
void Rotation::turnBackRightPivot(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to LineTracer::run is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  angle = abs(angle);
  int leftPwm = pwm;
  int rightPwm = 3;
  controller.resetMotorCount();
  double motorCount = 0;
  double targetMotorCount = calculate(angle);

  while(motorCount <= targetMotorCount) {
    if(pwm == 0) break;

    double leftCountRate = 1 - (abs(measurer.getLeftCount()) / targetMotorCount);
    leftPwm = pwm * leftCountRate > PIVOT_FRONT_MIN_PWM ? (int)(pwm * leftCountRate)
                                                        : PIVOT_FRONT_MIN_PWM;

    motorCount = (abs(measurer.getLeftCount()) + abs(measurer.getRightCount())) / 2;

    controller.setLeftMotorPwm(-leftPwm);
    controller.setRightMotorPwm(rightPwm);

    controller.sleep();
  }

  controller.stopMotor();
}

//設定された角度とPWM値で左タイヤを軸に前方へピボットターンする
void Rotation::turnForwardLeftPivot(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to LineTracer::run is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  int leftPwm = -1;
  int rightPwm = pwm;
  controller.resetMotorCount();
  double motorCount = 0;
  double targetMotorCount = calculate(angle);

  while(motorCount <= targetMotorCount) {
    if(pwm == 0) break;

    double rightCountRate = 1 - (measurer.getRightCount() / targetMotorCount);
    rightPwm = pwm * rightCountRate > PIVOT_FRONT_MIN_PWM ? (int)(pwm * rightCountRate)
                                                          : PIVOT_FRONT_MIN_PWM;

    controller.setLeftMotorPwm(leftPwm);
    controller.setRightMotorPwm(rightPwm);
    controller.sleep();

    motorCount = ((measurer.getLeftCount()) + (measurer.getRightCount())) / 2;
  }

  controller.stopMotor();
}

//設定された角度とPWM値で左タイヤを軸に後方へピボットターンする
void Rotation::turnBackLeftPivot(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to LineTracer::run is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  angle = abs(angle);
  int leftPwm = 3;
  int rightPwm = pwm;
  controller.resetMotorCount();
  double motorCount = 0;
  double targetMotorCount = calculate(angle);

  while(motorCount <= targetMotorCount) {
    if(pwm == 0) break;

    //徐々に速度を遅くする処理
    double rightCountRate = 1 - (abs(measurer.getRightCount()) / targetMotorCount);
    rightPwm = pwm * rightCountRate > PIVOT_FRONT_MIN_PWM ? (int)(pwm * rightCountRate)
                                                          : PIVOT_FRONT_MIN_PWM;

    controller.setLeftMotorPwm(leftPwm);
    controller.setRightMotorPwm(-rightPwm);

    motorCount = (abs(measurer.getLeftCount()) + abs(measurer.getRightCount())) / 2;

    controller.sleep();
  }

  controller.stopMotor();
}

double Rotation::calculate(int angle)
{
  // @see https://shogo82148.github.io/homepage/memo/tenchijin/odmetry.html
  const double transform = 2.0 * RADIUS / TREAD;
  return angle / transform;
}