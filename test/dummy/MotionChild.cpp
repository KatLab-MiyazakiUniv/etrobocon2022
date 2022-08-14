/**
 * @file MotionChild.cpp
 * @brief Motionの子クラス(ダミー)
 * @author kodama0720 mutotaka0426
 */

#include "MotionChild.h"

MotionChild::MotionChild(double _targetDistance, int _pwm)
  : targetDistance(_targetDistance), pwm(_pwm)
{
}

void MotionChild::run()
{
  // 動作の実装の一例として右方向への旋回を実装する
  int initialRightCount = measurer.getRightCount();
  int initialLeftCount = measurer.getLeftCount();
  double initialDistance = Mileage::calculateMileage(initialRightCount, initialLeftCount);

  double currentDistance = initialDistance;

  while(currentDistance - initialDistance < targetDistance) {
    controller.setLeftMotorPwm(pwm);
    controller.setRightMotorPwm(pwm / 2);

    int currentLeftMotorCount = measurer.getLeftCount();
    int currentRightMotorCount = measurer.getRightCount();
    currentDistance = Mileage::calculateMileage(currentLeftMotorCount, currentRightMotorCount);
  }
}

void MotionChild::logRunning()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保存する

  sprintf(buf, "Run MotionChild (targetDistance: %.2f, pwm: %d)", targetDistance, pwm);
  logger.log(buf);
}
