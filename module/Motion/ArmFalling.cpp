/**
 * @file   ArmFalling.cpp
 * @brief  アームを下げるクラス
 * @author KakinokiKanta sap2368
 */

#include "ArmFalling.h"

using namespace std;

ArmFalling::ArmFalling(int _angle, int _pwm) : angle(_angle), pwm(_pwm) {}

void ArmFalling::run()
{
  int initCount = measurer.getArmMotorCount();

  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  // pwm値が0以下の場合はwarningを出して終了する
  if(pwm <= 0) {
    snprintf(buf, BUF_SIZE, "The pwm value passed to ArmFalling is %d", pwm);
    logger.logWarning(buf);
    return;
  }

  // pwmが40より大きい場合はwarningを出してpwmを40にする
  if(pwm > 40) {
    snprintf(buf, BUF_SIZE, "The pwm value passed to ArmFalling is %d", pwm);
    logger.logWarning(buf);
    pwm = 40;
  }

  // angleが0以下の場合はwarningを出して終了する
  if(angle <= 0) {
    snprintf(buf, BUF_SIZE, "The angle value passed to ArmFalling is %d", angle);
    logger.logWarning(buf);
    return;
  }

  // angleが60より大きい場合はwarningを出してangleを60にする
  if(angle > 60) {
    snprintf(buf, BUF_SIZE, "The angle value passed to ArmFalling is %d", angle);
    logger.logWarning(buf);
    angle = 60;
  }

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
}

void ArmFalling::logRunning()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域

  snprintf(buf, BUF_SIZE, "Run ArmFalling (angle: %d, pwm: %d)", angle, pwm);
  logger.log(buf);
}
