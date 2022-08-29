/**
 * @file   ArmRising.cpp
 * @brief  アームを上げるクラス
 * @author mutotaka0426 KakinokiKanta
 */

#include "ArmRising.h"

using namespace std;

ArmRising::ArmRising(int _angle, int _pwm) : angle(_angle), pwm(_pwm) {}

void ArmRising::run()
{
  int initCount = measurer.getArmMotorCount();

  while(true) {
    int currentCount = measurer.getArmMotorCount();

    if(currentCount < initCount - angle) {
      break;
    }
    controller.setArmMotorPwm(-pwm);
    // 10ミリ秒待機
    controller.sleep();
  }

  //アームモータの停止
  controller.stopArmMotor();
}

void ArmRising::logRunning()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, BUF_SIZE, "Run ArmRising (angle: %d, pwm: %d)", angle, pwm);
  logger.log(buf);
}
