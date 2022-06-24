/**
 * @file StraightRunner.cpp
 * @brief 直進クラス
 * @author sugaken0528
 */

#include "StraightRunner.h"

StraightRunner::StraightRunner() {}

// 設定された距離を直進する
void StraightRunner::runStraightToDistance(double targetDistance, int pwm)
{
  // 直進前の走行距離
  int initialRightMotorCount = measurer.getRightCount();
  int initialLeftMotorCount = measurer.getLeftCount();
  double initialDistance = Mileage::calculateMileage(initialRightMotorCount, initialLeftMotorCount);
  // 直進中の走行距離
  int currentRightMotorCount = 0;
  int currentLeftMotorCount = 0;
  double currentDistance = 0;
  int error = 0;                // 左右の回転数の誤差
  Pid pid(1.2, 0.3, 0.001, 0);  // 左右の回転数を合わせるためのPID
  int adjustment = 0;           // 左右の誤差の補正値

  // 現在のpwm値
  int currentPwm = 0;

  // 距離の値が負または、pwm値が0の際は、終了する
  if(targetDistance < 0 || pwm == 0) return;

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
      // 調整距離毎にPWM値を加速値分だけ上げていく
      currentPwm
          = currentDistance / SECTION_DISTANCE * ACCELE_PWM + ACCELE_PWM * ((pwm > 0) ? 1 : -1);
      if(std::abs(currentPwm) > std::abs(pwm)) {
        currentPwm = pwm;
      }
    }

    // 左右のモーターカウントを合わせるための補正値計算
    error = (currentLeftMotorCount - initialLeftMotorCount)
            - (currentRightMotorCount - initialRightMotorCount);
    adjustment = static_cast<int>(pid.calculatePid(error));

    // モータのPWM値をセット
    controller.setLeftMotorPwm(currentPwm + adjustment);
    controller.setRightMotorPwm(currentPwm - adjustment);

    // 10ミリ秒待機
    controller.sleep();
  }
  // モータの停止
  controller.stopMotor();
}
