/**
 * @file   ColorStraight.cpp
 * @brief  指定色直進動作
 * @author sugaken0528 kawanoichi mutotaka0426
 */

#include "ColorStraight.h"
using namespace std;

ColorStraight::ColorStraight(COLOR _targetColor, int _pwm)
  : targetColor(_targetColor), pwm(_pwm)
{
}

void ColorStraight::run()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保存する領域

  // pwm値が0の場合は終了する
  if(pwm == 0) {
    logger.logWarning("The pwm value passed to ColorStraight is 0");
    return;
  }
  // pwmの絶対値がMIN_PWMより小さい場合はwarningを出す
  if(abs(pwm) < MIN_PWM) {
    snprintf(buf, BUF_SIZE, "The pwm value passed to ColorStraight is %d", pwm);
    logger.logWarning(buf);
  }
  // 目標の色がNoneのときwarningを出して終了する
  if(targetColor == COLOR::NONE) {
    logger.logWarning("The targetColor passed to ColorStraight is NONE");
    return;
  }

  // 直進前の走行距離
  int initialRightMotorCount = measurer.getRightCount();
  int initialLeftMotorCount = measurer.getLeftCount();

  int count = 0;                  // ループ回数
  int currentPwm = 0;             // 現在のpwm値
  int sign = (pwm > 0) ? 1 : -1;  // 加速させる向き（符号）
  int error = 0;                  // 左右の回転数の誤差
  Pid pid(0.5, 0.3, 0.001, 0);    // 左右の回転数を合わせるためのPID
  int adjustmentPwm = 0;          // 左右の誤差の補正値
  COLOR color = COLOR::NONE;

  while(true) {
    // 現在のRGB値から色を識別する
    color = ColorJudge::getColor(measurer.getRawColor());

    // 指定された色を検出した場合、直進終了
    if(color == targetColor) {
      break;
    }

    //現在の距離を取得する
    int currentRightMotorCount = measurer.getRightCount();
    int currentLeftMotorCount = measurer.getLeftCount();

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

    // モータのPWM値をセット
    controller.setLeftMotorPwm(currentPwm + adjustmentPwm);
    controller.setRightMotorPwm(currentPwm - adjustmentPwm);

    // 10ミリ秒待機
    controller.sleep();
  }
  // モータの停止
  controller.stopMotor();
}

void ColorStraight::logRunning()
{
  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保存する領域

  snprintf(buf, BUF_SIZE, "Run ColorStraight (targetColor: %s, pwm: %d)",
          ColorJudge::colorToString(targetColor), pwm);
  logger.log(buf);
}
