/**
 * @file Controller.cpp
 * @brief モーター制御
 * @author sakakibara
 */
#include "Controller.h"

Controller::Controller() : rightWheel(PORT_B), leftWheel(PORT_C), armMotor(PORT_A) {}

int Controller::limitPwmValue(const int value)
{
  if (value > MOTOR_PWM_MAX)
  {
    return MOTOR_PWM_MAX;
  }
  else if (value < MOTOR_PWM_MIN)
  {
    return MOTOR_PWM_MIN;
  }
  return value;
}

// PWM値を右モータにセット
void Controller::setRightMotorPwm(const int pwm)
{
  rightWheel.setPWM(limitPwmValue(pwm));
}

// PWM値を左モータにセット
void Controller::setLeftMotorPwm(const int pwm)
{
  leftWheel.setPWM(limitPwmValue(pwm));
}

//タイヤのモータを停止する
void Controller::stopMotor()
{
  leftWheel.stop();
  rightWheel.stop();
}

// PWM値をアームのモータにセット
void Controller::setArmMotorPwm(const int pwm)
{
  armMotor.setPWM(limitPwmValue(pwm));
}

//アームのモータを停止
void Controller::stopArmMotor()
{
  armMotor.stop();
}

//スリープ
void Controller::sleep(int milliSec)
{
  clock.sleep(milliSec);
}

// //シミュレータへ競技の終了を通知する
// void Controller::notifyCompletedToSimulator()
// {
//   ETRoboc_notifyCompletedToSimulator();
// }
