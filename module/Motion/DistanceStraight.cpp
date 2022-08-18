/**
 * @file   DistanceStraight.cpp
 * @brief  指定距離直進動作
 * @author sugaken0528 kawanoichi mutotaka0426
 */

#include "DistanceStraight.h"
using namespace std;

DistanceStraight::DistanceStraight(double _targetDistance, int _pwm)
  : targetDistance(_targetDistance), pwm(_pwm)
{
}

void DistanceStraight::run()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  // pwmが0の場合は終了する
  if(pwm == 0) {
    logger.logWarning("The pwm value passed to DistanceStraight is 0");
    return;
  }
  // pwmの絶対値がMIN_PWMより小さい場合はwarningを出す
  if(abs(pwm) < MIN_PWM) {
    snprintf(buf, BUF_SIZE, "The pwm value passed to DistanceStraight is less than %d", MIN_PWM);
    logger.logWarning(buf);
  }
  // 目標距離の値が0以下の場合はwarningを出して終了する
  if(targetDistance <= 0) {
    snprintf(buf, BUF_SIZE, "The targetDistance value passed to DistanceStraight is %.2f",
             targetDistance);
    logger.logWarning(buf);
    return;
  }

  // 直進前の走行距離
  int initialRightMotorCount = measurer.getRightCount();
  int initialLeftMotorCount = measurer.getLeftCount();
  double initialDistance = Mileage::calculateMileage(initialRightMotorCount, initialLeftMotorCount);

  // 直進中の走行距離
  int currentRightMotorCount = initialRightMotorCount;
  int currentLeftMotorCount = initialLeftMotorCount;
  double currentDistance = initialDistance;
  // ループ回数
  int count = 0;
  // 現在のpwm値
  int currentPwm = 0;
  int sign = (pwm > 0) ? 1 : -1;
  int error = 0;                // 左右の回転数の誤差
  Pid pid(0.5, 0.3, 0.001, 0);  // 左右の回転数を合わせるためのPID
  int adjustmentPwm = 0;        // 左右の誤差の補正値

  // 走行距離が目標距離に到達するまで繰り返す
  while(true) {
    //現在の距離を取得する
    currentRightMotorCount = measurer.getRightCount();
    currentLeftMotorCount = measurer.getLeftCount();
    currentDistance = Mileage::calculateMileage(currentLeftMotorCount, currentRightMotorCount);

    //現在の距離が目標距離に到達したらループを終了する
    if(abs(currentDistance - initialDistance) >= targetDistance) {
      break;
    }

    // PWM値を徐々に目標値に合わせる
    if(currentPwm != pwm) {
      // ループ毎にPWM値を加速値分だけ上げていく
      currentPwm = (MIN_PWM + (ACCELE_PWM * count)) * sign;
      if(abs(currentPwm) > abs(pwm)) {
        currentPwm = pwm;
      }
      count++;
    }

    // 左右のモーターカウントを合わせるための補正値計算
    error = (currentLeftMotorCount - initialLeftMotorCount)
            - (currentRightMotorCount - initialRightMotorCount);
    adjustmentPwm = static_cast<int>(pid.calculatePid(error));

    // モータにPWM値をセット
    controller.setLeftMotorPwm(currentPwm + adjustmentPwm);
    controller.setRightMotorPwm(currentPwm - adjustmentPwm);

    // 10ミリ秒待機
    controller.sleep();
  }
  // モータの停止
  controller.stopMotor();
}

void DistanceStraight::logRunning()
{
  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, BUF_SIZE, "Run DistanceStraight (targetDistance: %.2f, pwm: %d)", targetDistance,
           pwm);
  logger.log(buf);
}
