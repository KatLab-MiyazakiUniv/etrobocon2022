/**
 * @file StraightRunner.cpp
 * @brief 直進クラス
 * @author sugaken0528 kawanoichi
 */

#include "StraightRunner.h"

StraightRunner::StraightRunner() {}

// 指定された距離を直進する
void StraightRunner::run(double targetDistance, int pwm)
{
  // pwmの絶対値がMIN_PWMより小さい場合はwarningを出す
  if(std::abs(pwm) < MIN_PWM) {
    char errorMessage[64];
    std::sprintf(errorMessage, "The pwm value passed to StraightRunner::run is %d", pwm);
    logger.logWarning(errorMessage);
    // pwmが0の場合は終了する
    if(pwm == 0) {
      return;
    }
  }
  // 目標距離の値が負の場合はwarningを出して終了する
  if(targetDistance < 0) {
    logger.logWarning("The targetDistance value passed to StraightRunner::run is negative");
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
    if(std::abs(currentDistance - initialDistance) >= targetDistance) {
      break;
    }

    // PWM値を徐々に目標値に合わせる
    if(currentPwm != pwm) {
      // ループ毎にPWM値を加速値分だけ上げていく
      currentPwm = (MIN_PWM + (ACCELE_PWM * count)) * sign;
      if(std::abs(currentPwm) > std::abs(pwm)) {
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

// 指定した色を検出するまで直進する
void StraightRunner::runToColor(COLOR targetColor, int pwm)
{
  // pwmの絶対値がMIN_PWMより小さい場合はwarningを出す
  if(std::abs(pwm) < MIN_PWM) {
    char errorMessage[64];
    std::sprintf(errorMessage, "The pwm value passed to StraightRunner::runToColor is %d", pwm);
    logger.logWarning(errorMessage);
    // pwm値が0の場合は終了する
    if(pwm == 0) {
      return;
    }
  }
  // 目標の色がNoneのときwarningを出して終了する
  if(targetColor == COLOR::NONE) {
    logger.logWarning("The targetColor value passed to StraightRunner::runToColor is NONE");
    return;
  }

  // 直進前の走行距離
  int initialRightMotorCount = measurer.getRightCount();
  int initialLeftMotorCount = measurer.getLeftCount();
  double initialDistance = Mileage::calculateMileage(initialRightMotorCount, initialLeftMotorCount);

  // 直進中の走行距離
  int currentRightMotorCount = initialRightMotorCount;
  int currentLeftMotorCount = initialRightMotorCount;
  double currentDistance = initialDistance;
  // ループ回数
  int count = 0;
  // 現在のpwm値
  int currentPwm = 0;
  int sign = (pwm > 0) ? 1 : -1;
  int error = 0;                // 左右の回転数の誤差
  Pid pid(0.5, 0.3, 0.001, 0);  // 左右の回転数を合わせるためのPID
  int adjustmentPwm = 0;        // 左右の誤差の補正値
  COLOR color = COLOR::NONE;

  while(true) {
    // 現在のRGB値から色を識別する
    color = ColorJudge::getColor(measurer.getRawColor());

    // 指定された色を検出した場合、直進終了
    if(color == targetColor) {
      break;
    }

    //現在の距離を取得する
    currentRightMotorCount = measurer.getRightCount();
    currentLeftMotorCount = measurer.getLeftCount();
    currentDistance = Mileage::calculateMileage(currentLeftMotorCount, currentRightMotorCount);

    // PWM値を徐々に目標値に合わせる
    if(currentPwm != pwm) {
      // ループ毎にPWM値を加速値分だけ上げていく
      currentPwm = (MIN_PWM + (ACCELE_PWM * count)) * sign;
      if(std::abs(currentPwm) > std::abs(pwm)) {
        currentPwm = pwm;
      }
      count++;
    }

    // 左右のモーターカウントを合わせるための補正値計算
    error = (currentLeftMotorCount - initialLeftMotorCount)
            - (currentRightMotorCount - initialRightMotorCount);
    adjustmentPwm = static_cast<int>(pid.calculatePid(error));

    // モータのPWM値をセット
    controller.setLeftMotorPwm(currentPwm + adjustmentPwm);
    controller.setRightMotorPwm(currentPwm - adjustmentPwm);

    // 10ミリ秒待機
    controller.sleep();
  }
  // モータの停止
  controller.stopMotor();
}