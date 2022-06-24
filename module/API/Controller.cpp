/**
 * @file Controller.cpp
 * @brief モーター制御に用いる関数をまとめたラッパークラス
 * @author sap2368
 */
#include "Controller.h"

Controller::Controller() : rightWheel(PORT_B), leftWheel(PORT_C), armMotor(PORT_A) {}

int Controller::limitPwmValue(const int value)
{
  if(value > MOTOR_PWM_MAX) {
    return MOTOR_PWM_MAX;
  } else if(value < MOTOR_PWM_MIN) {
    return MOTOR_PWM_MIN;
  }
  return value;
}

// 右モータにPWM値をセット
void Controller::setRightMotorPwm(const int pwm)
{
  rightWheel.setPWM(limitPwmValue(pwm));
}

// 左モータにPWM値をセット
void Controller::setLeftMotorPwm(const int pwm)
{
  leftWheel.setPWM(limitPwmValue(pwm));
}

// タイヤのモータを停止する
void Controller::stopMotor()
{
  leftWheel.stop();
  rightWheel.stop();
}

// アームのモータにPWM値をセット
void Controller::setArmMotorPwm(const int pwm)
{
  armMotor.setPWM(limitPwmValue(pwm));
}

// アームのモータを停止する
void Controller::stopArmMotor()
{
  armMotor.stop();
}

// 自タスクスリープ（デフォルトは10ミリ秒）
void Controller::sleep(int microSec)
{
  clock.sleep(microSec);
}
