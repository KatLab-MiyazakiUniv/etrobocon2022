/**
 * @file Rotation.cpp
 * @brief 回頭・ピボットターンする
 * @author sugaken0528
 */

#include "Rotation.h"

using namespace std;

Rotation::Rotation()
  : RADIUS(50.0), TREAD(125.0), ROTATE_MIN_PWM(40), PIVOT_FRONT_MIN_PWM(40), PIVOT_BACK_MIN_PWM(40)
{
}

//左に回頭する
void Rotation::rotateLeft(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to Rotation::rotateLeft is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  int leftSign = -1;
  int rightSign = 1;
  double targetDistance
      = M_PI * TREAD * abs(angle) / 360;  // 指定した角度に対する目標の走行距離(弧の長さ)
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

    // モータにPWM値をセット
    controller.setLeftMotorPwm(abs(pwm) * leftSign);
    controller.setRightMotorPwm(abs(pwm) * rightSign);

    // 10ミリ秒待機
    controller.sleep();
  }

  //モータの停止
  controller.stopMotor();
}

//右に回頭する
void Rotation::rotateRight(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to Rotation::rotateRight is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  int leftSign = 1;
  int rightSign = -1;
  double targetDistance
      = M_PI * TREAD * abs(angle) / 360;  //指定した角度に対する目標の走行距離(弧の長さ)
  // 目標距離（呼び出し時の走行距離 ± 目標の走行距離）
  double targetLeftDistance
      = Mileage::calculateWheelMileage(measurer.getLeftCount()) + targetDistance * leftSign;
  double targetRightDistance
      = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance * rightSign;

  // 両輪が目標距離に到達するまでループ
  while(leftSign != 0 || rightSign != 0) {
    // 残りの移動距離 (目標の走行距離 - 現在の走行距離)
    double diffLeftDistance
        = (targetLeftDistance - Mileage::calculateWheelMileage(measurer.getLeftCount())) * leftSign;
    double diffRightDistance
        = (targetRightDistance - Mileage::calculateWheelMileage(measurer.getRightCount()))
          * rightSign;

    // 目標の走行距離に到達した場合
    if(diffLeftDistance <= 0) {
      leftSign = 0;
    }
    if(diffRightDistance <= 0) {
      rightSign = 0;
    }

    // モータにPWM値をセット
    controller.setLeftMotorPwm(abs(pwm) * leftSign);
    controller.setRightMotorPwm(abs(pwm) * rightSign);

    // 10ミリ秒待機
    controller.sleep();
  }

  //モータの停止
  controller.stopMotor();
}

// 右タイヤを軸に前方へピボットターンする
void Rotation::turnForwardRightPivot(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to Rotation::turnForwardRightPivot is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  int leftPwm = pwm;
  int rightPwm = -1;  // 軸がぶれるのを防止するため軸タイヤのモータ(右モータ)にセットするPWM値

  // モータ回転量をリセット
  controller.resetMotorCount();

  double motorCount = 0;
  double targetMotorCount
      = calculateTireAngle(angle);  // 指定した回転角度に対する目標のモータ回転量

  while(motorCount <= targetMotorCount) {
    if(pwm == 0) break;

    // 現在のモータ回転量を取得
    motorCount = (measurer.getLeftCount() + measurer.getRightCount()) / 2;

    // モータにPWM値をセット
    controller.setLeftMotorPwm(leftPwm);
    controller.setRightMotorPwm(rightPwm);

    // 10ミリ秒待機
    controller.sleep();
  }

  // モータの停止
  controller.stopMotor();
}

// 右タイヤを軸に後方へピボットターンする
void Rotation::turnBackRightPivot(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to Rotation::turnBackRightPivot is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  angle = abs(angle);
  int leftPwm = pwm;
  int rightPwm = 3;  // 軸がぶれるのを防止するため軸タイヤのモータ(右モータ)にセットするPWM値

  // モータ回転量をリセット
  controller.resetMotorCount();

  double motorCount = 0;
  double targetMotorCount
      = calculateTireAngle(angle);  // 指定した回転角度に対する目標のモータ回転量

  while(motorCount <= targetMotorCount) {
    if(pwm == 0) break;

    // 現在のモータ回転量を取得
    motorCount = (abs(measurer.getLeftCount()) + abs(measurer.getRightCount())) / 2;

    // モータにPWM値をセット
    controller.setLeftMotorPwm(-leftPwm);
    controller.setRightMotorPwm(rightPwm);

    // 10ミリ秒待機
    controller.sleep();
  }

  // モータの停止
  controller.stopMotor();
}

// 左タイヤを軸に前方へピボットターンする
void Rotation::turnForwardLeftPivot(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to Rotation::turnForwardLeftPivot is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }
  int leftPwm = -1;  // 軸がぶれるのを防止するため軸タイヤのモータ(左モータ)にセットするPWM値
  int rightPwm = pwm;

  // モータ回転量をリセット
  controller.resetMotorCount();

  double motorCount = 0;
  double targetMotorCount
      = calculateTireAngle(angle);  // 指定した回転角度に対する目標のモータ回転量

  while(motorCount <= targetMotorCount) {
    if(pwm == 0) break;

    // 現在のモータ回転量を取得
    motorCount = ((measurer.getLeftCount()) + (measurer.getRightCount())) / 2;

    // モータにPwm値をセット
    controller.setLeftMotorPwm(leftPwm);
    controller.setRightMotorPwm(rightPwm);

    // 10ミリ秒待機
    controller.sleep();
  }

  // モータの停止
  controller.stopMotor();
}

//　左タイヤを軸に後方へピボットターンする
void Rotation::turnBackLeftPivot(int angle, int pwm)
{
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    printf("\x1b[36m"); /* 文字色をシアンに */
    printf("warning: The pwm value passed to Rotation::turnBackLeftPivot is 0\n");
    printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
    return;
  }

  angle = abs(angle);
  int leftPwm = 3;  // 軸がぶれるのを防止するため軸タイヤのモータ(左モータ)にセットするPWM値
  int rightPwm = pwm;

  // モータ回転量をリセット
  controller.resetMotorCount();

  double motorCount = 0;
  double targetMotorCount
      = calculateTireAngle(angle);  // 指定した回転角度に対する目標のモータ回転量

  while(motorCount <= targetMotorCount) {
    if(pwm == 0) break;

    // 現在のモータ回転量を取得
    motorCount = (abs(measurer.getLeftCount()) + abs(measurer.getRightCount())) / 2;

    // モータにPWM値をセット
    controller.setLeftMotorPwm(leftPwm);
    controller.setRightMotorPwm(-rightPwm);

    // 10ミリ秒待機
    controller.sleep();
  }

  // モータの停止
  controller.stopMotor();
}

// 指定された角度回頭したときの片輪の回転角度を計算する
double Rotation::calculateTireAngle(int angle)
{
  // @see https://shogo82148.github.io/homepage/memo/tenchijin/odmetry.html
  const double transform = 2.0 * RADIUS / TREAD;
  return angle / transform;
}