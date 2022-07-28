/**
 * @file LineTracer.cpp
 * @brief ライントレースをするクラス
 * @author mutotaka0426 kodama0720
 */

#include "LineTracer.h"
using namespace std;

LineTracer::LineTracer(bool& _isLeftEdge) : isLeftEdge(_isLeftEdge) {}

void LineTracer::run(double targetDistance, int targetBrightness, int pwm, const PidGain& gain)
{
  double initialDistance = 0;
  double currentDistance = 0;
  int currentPid = 0;
  int sign = 0;
  Pid pid(gain.kp, gain.ki, gain.kd, targetBrightness);
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    logger.logWarning("The pwm value passed to LineTracer::run is 0");
    return;
  }

  //左右で符号を変える
  sign = isLeftEdge ? -1 : 1;

  // 初期値を格納
  initialDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
  currentDistance = initialDistance;

  //走行距離が目標距離に到達するまで繰り返す
  while(abs(currentDistance - initialDistance) < targetDistance) {
    currentDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // PID計算
    currentPid = pid.calculatePid(measurer.getBrightness()) * sign;

    //モータのPWM値をセット（0を超えないようにセット）
    int rightPwm = pwm > 0 ? max(pwm - (int)currentPid, 0) : min(pwm - (int)currentPid, 0);
    int leftPwm = pwm > 0 ? max(pwm + (int)currentPid, 0) : min(pwm + (int)currentPid, 0);
    controller.setRightMotorPwm(rightPwm);
    controller.setLeftMotorPwm(leftPwm);
    // 10ミリ秒待機
    controller.sleep();
  }
  //モータの停止
  controller.stopMotor();
}

void LineTracer::runToColor(COLOR targetColor, int targetBrightness, int pwm, const PidGain& gain)
{
  int currentPid = 0;
  int sign = 0;
  Pid pid(gain.kp, gain.ki, gain.kd, targetBrightness);
  COLOR currentColor = COLOR::NONE;
  int colorCount = 0;
  // pwm値が0の場合はwarningを出して終了する
  if(pwm == 0) {
    logger.logWarning("The pwm value passed to LineTracer::runToColor is 0");
    return;
  }

  //左右で符号を変える
  sign = isLeftEdge ? -1 : 1;

  //指定された色をJUDGE_COUNT回連続で取得するまで繰り返す
  while(colorCount < JUDGE_COUNT) {
    currentColor = ColorJudge::getColor(measurer.getRawColor());
    if(currentColor == targetColor) {
      colorCount++;
    } else {
      colorCount = 0;
    }
    // PID計算
    currentPid = pid.calculatePid(measurer.getBrightness()) * sign;

    //モータのPWM値をセット（0を超えないようにセット）
    int rightPwm = pwm > 0 ? max(pwm - (int)currentPid, 0) : min(pwm - (int)currentPid, 0);
    int leftPwm = pwm > 0 ? max(pwm + (int)currentPid, 0) : min(pwm + (int)currentPid, 0);
    controller.setRightMotorPwm(rightPwm);
    controller.setLeftMotorPwm(leftPwm);
    // 10ミリ秒待機
    controller.sleep();
  }
  //モータの停止
  controller.stopMotor();
}

bool LineTracer::getIsLeftEdge()
{
  return isLeftEdge;
}

void LineTracer::setIsLeftEdge(bool _isLeftEdge)
{
  isLeftEdge = _isLeftEdge;
}

void LineTracer::toggleEdge()
{
  isLeftEdge = !isLeftEdge;
}
