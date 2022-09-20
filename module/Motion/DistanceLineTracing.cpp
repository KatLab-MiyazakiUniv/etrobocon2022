/**
 * @file   DistanceLineTracing.cpp
 * @brief  指定距離ライントレース動作
 * @author mutotaka0426 kodama0720
 */

#include "DistanceLineTracing.h"
using namespace std;

DistanceLineTracing::DistanceLineTracing(double _targetDistance, int _targetBrightness, int _pwm,
                                         const PidGain& _gain, bool& _isLeftEdge)
  : targetDistance(_targetDistance),
    targetBrightness(_targetBrightness),
    pwm(_pwm),
    gain(_gain),
    isLeftEdge(_isLeftEdge)
{
}

void DistanceLineTracing::run()
{
  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  double initialDistance = 0;  // 実行前の走行距離
  double currentDistance = 0;  // 現在の走行距離
  int currentPid = 0;
  int sign = 0;
  Pid pid(gain.kp, gain.ki, gain.kd, targetBrightness);

  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    logger.logWarning("The pwm value passed to DistanceLineTracing is 0");
    return;
  }
  if(targetDistance <= 0) {
    snprintf(buf, BUF_SIZE, "The targetDistance value passed to DistanceLineTracing is %.2f",
             targetDistance);
    logger.logWarning(buf);
    return;
  }

  // 左右で符号を変える
  sign = isLeftEdge ? -1 : 1;

  // 初期値を格納
  initialDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());

  // 走行距離が目標距離に到達するまで繰り返す
  while(true) {
    currentDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 走行距離が目標距離に到達
    if(abs(currentDistance - initialDistance) >= targetDistance) break;

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

void DistanceLineTracing::logRunning()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域
  const char* str = isLeftEdge ? "true" : "false";

  snprintf(buf, BUF_SIZE,
           "Run DistanceLineTracing (targetDistance: %.2f, targetBrightness: %d, pwm: %d, gain: "
           "(%.2f,%.2f,%.2f), isLeftEdge: %s)",
           targetDistance, targetBrightness, pwm, gain.kp, gain.ki, gain.kd, str);
  logger.log(buf);
}
