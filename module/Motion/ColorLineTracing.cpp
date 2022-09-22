/**
 * @file   ColorLineTracing.cpp
 * @brief  指定色ライントレース動作
 * @author mutotaka0426 kodama0720
 */

#include "ColorLineTracing.h"
using namespace std;

ColorLineTracing::ColorLineTracing(COLOR _targetColor, int _targetBrightness, int _pwm,
                                   const PidGain& _gain, bool& _isLeftEdge)
  : targetColor(_targetColor),
    targetBrightness(_targetBrightness),
    pwm(_pwm),
    gain(_gain),
    isLeftEdge(_isLeftEdge)
{
}

void ColorLineTracing::run()
{
  int currentPid = 0;
  int sign = 0;
  Pid pid(gain.kp, gain.ki, gain.kd, targetBrightness);
  COLOR currentColor = COLOR::NONE;
  int colorCount = 0;

  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    logger.logWarning("The pwm value passed to ColorLineTracing is 0");
    return;
  }
  // 目標の色がNoneのときwarningを出して終了する
  if(targetColor == COLOR::NONE) {
    logger.logWarning("The targetColor passed to ColorLineTracing is NONE");
    return;
  }

  // 左右で符号を変える
  sign = isLeftEdge ? -1 : 1;

  // 指定された色をJUDGE_COUNT回連続で取得するまで繰り返す
  while(true) {
    currentColor = ColorJudge::getColor(measurer.getRawColor());
    if(currentColor == targetColor) {
      colorCount++;
    } else {
      colorCount = 0;
    }
    // 指定された色をJUDGE_COUNT回連続で取得
    if(colorCount == JUDGE_COUNT) break;

    // PID計算
    currentPid = pid.calculatePid(measurer.getBrightness()) * sign;

    // モータのPWM値をセット（0を超えないようにセット）
    int rightPwm = pwm > 0 ? max(pwm - (int)currentPid, 0) : min(pwm + (int)currentPid, 0);
    int leftPwm = pwm > 0 ? max(pwm + (int)currentPid, 0) : min(pwm - (int)currentPid, 0);
    controller.setRightMotorPwm(rightPwm);
    controller.setLeftMotorPwm(leftPwm);
    // 10ミリ秒待機
    controller.sleep();
  }
  // モータの停止
  controller.stopMotor();
}

void ColorLineTracing::logRunning()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* str = isLeftEdge ? "true" : "false";

  snprintf(buf, BUF_SIZE,
           "Run ColorLineTracing (targetColor: %s, targetBrightness: %d, pwm: %d, gain: "
           "(%.2f,%.2f,%.2f), isLeftEdge: %s)",
           ColorJudge::colorToString(targetColor), targetBrightness, pwm, gain.kp, gain.ki, gain.kd,
           str);
  logger.log(buf);
}
