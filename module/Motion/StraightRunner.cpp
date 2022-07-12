/**
 * @file StraightRunner.cpp
 * @brief 直進クラス
 * @author sugaken0528
 */

#include "StraightRunner.h"

StraightRunner::StraightRunner() {}

// 指定された距離を直進する
void StraightRunner::run(double targetDistance, int pwm)
{
  Logger logger;

  // 目標距離の値が負またはpwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    logger.logWarning(" The pwm value passed to StraightRunner::run is 0 ");
    return;
  } else if(targetDistance < 0) {
    logger.logWarning(" The targetDistance value passed to StraightRunner::run is negative ");
    return;
  }

  // 直進前の走行距離
  int initialRightMotorCount = measurer.getRightCount();
  int initialLeftMotorCount = measurer.getLeftCount();
  double initialDistance = Mileage::calculateMileage(initialRightMotorCount, initialLeftMotorCount);

  // 直進中の走行距離
  int currentRightMotorCount = 0;
  int currentLeftMotorCount = 0;
  double currentDistance = 0;
  // ループ回数
  int count = 0;
  // 現在のpwm値
  int currentPwm = 0;
  int sign = (pwm > 0) ? 1 : -1;

  // 走行距離が目標距離に到達するまで繰り返す
  while(true) {
    //現在の距離を取得する
    currentRightMotorCount = measurer.getRightCount();
    currentLeftMotorCount = measurer.getLeftCount();
    currentDistance = Mileage::calculateMileage(currentLeftMotorCount, currentRightMotorCount);

    //現在の距離が目標距離に到達したらループを終了する
    if(std::abs(currentDistance - initialDistance) >= targetDistance) {
      break;
    }

    // PWM値を徐々に目標値に合わせる
    if(currentPwm != pwm) {
      // ループ毎にPWM値を加速値分だけ上げていく
      currentPwm = MIN_PWM + (ACCELE_PWM * count) * sign;
      if(std::abs(currentPwm) > std::abs(pwm)) {
        currentPwm = pwm;
      }
      count++;
    }

    // モータにPWM値をセット
    controller.setLeftMotorPwm(currentPwm);
    controller.setRightMotorPwm(currentPwm);

    // 10ミリ秒待機
    controller.sleep();
  }
  // モータの停止
  controller.stopMotor();
}
