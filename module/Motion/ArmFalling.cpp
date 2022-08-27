/**
 * @file   ArmFalling.cpp
 * @brief  アームを下げるクラス
 * @author KakinokiKanta
 */

#include "ArmFalling.h"
#include "ArmKeeper.h"
using namespace std;

ArmFalling::ArmFalling(int _angle, int _pwm) : angle(_angle), pwm(_pwm) {}

void ArmFalling::run()
{
  int initCount = measurer.getArmMotorCount();

  while(true) {
    int currentCount = measurer.getArmMotorCount();

    if(currentCount > initCount + angle) {
      break;
    }
    controller.setArmMotorPwm(pwm);
    // 10ミリ秒待機
    controller.sleep();
  }

  //アームモータの停止
  controller.stopArmMotor();

  // アームを水平にする処理を有効化
  ArmKeeper::setKeepFlag(true);
}

void ArmFalling::logRunning()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, BUF_SIZE, "Run ArmFalling (angle: %d, pwm: %d)", angle, pwm);
  logger.log(buf);
}
