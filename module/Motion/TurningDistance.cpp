/**
 * @file   TurningDistance.cpp
 * @brief  指定距離旋回動作
 * @author mutotaka0426
 */

#include "TurningDistance.h"
using namespace std;

TurningDistance::TurningDistance(double _targetDistance, int _leftPwm, int _rightPwm)
  : targetDistance(_targetDistance), leftPwm(_leftPwm), rightPwm(_rightPwm)
{
}

void TurningDistance::run()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保存する

  // pwmが0の場合は終了する
  if(leftPwm == 0 && rightPwm == 0) {
    logger.logWarning("The pwm value passed to TurningDistance is 0");
    return;
  }
  // 目標距離の値が0以下の場合はwarningを出して終了する
  if(targetDistance <= 0) {
    sprintf(buf, "The targetDistance value passed to TurningDistance is %.2f", targetDistance);
    logger.logWarning(buf);
    return;
  }
  // pwmの絶対値が同じ場合は回頭or直進でいいためwarningを出す
  if(abs(leftPwm) == abs(rightPwm)) {
    logger.logWarning(
        "The absolute values of the left pwm value and the right pwm value are the same");
  }

  // 旋回前の走行距離(両輪の符号が異なる場合のために絶対値を取る)
  int initialRightMotorCount = measurer.getRightCount();
  int initialLeftMotorCount = measurer.getLeftCount();

  // 走行距離が目標距離に到達するまで繰り返す
  while(true) {
    //現在の走行距離を取得する
    int currentLeftMotorCount = abs(initialLeftMotorCount - measurer.getLeftCount());
    int currentRightMotorCount = abs(initialRightMotorCount - measurer.getRightCount());
    double currentDistance
        = Mileage::calculateMileage(currentLeftMotorCount, currentRightMotorCount);

    //現在の距離が目標距離に到達したらループを終了する
    if(currentDistance >= targetDistance) {
      break;
    }

    controller.setLeftMotorPwm(leftPwm);
    controller.setRightMotorPwm(rightPwm);

    // 10ミリ秒待機
    controller.sleep();
  }
  // モータの停止
  controller.stopMotor();
}

void TurningDistance::logRunning()
{
  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保存する

  sprintf(buf, "Run TurningDistance (targetDistance: %.2f, leftPwm: %d, rightPwm: %d)",
          targetDistance, leftPwm, rightPwm);
  logger.log(buf);
}
