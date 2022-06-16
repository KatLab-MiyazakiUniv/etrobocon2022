/**
 * @file Controller.h
 * @brief モーター制御に用いる関数をまとめたラッパークラス
 * @author sakakibara
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ev3api.h"
#include "Motor.h"
#include "Clock.h"

class Controller {
 public:
  static const int MOTOR_PWM_MAX = 100;
  static const int MOTOR_PWM_MIN = -100;

  Controller();

  /**
   * モータにPWM値をセット
   * @param pwm PWM値
   */
  void setRightMotorPwm(const int pwm);
  void setLeftMotorPwm(const int pwm);

  /**
   * タイヤのモータを停止する
   */
  void stopMotor();

  /**
   * アームにPWM値をセット
   * @param pwm PWM値
   */
  void setArmMotorPwm(const int pwm);

  /**
   * アームのモータを停止する
   */
  void stopArmMotor();

  /**
   * 自タスクスリープ
   * @param milliSec スリープ時間(ミリ秒)
   */
  void sleep(int milliSec = 10);

  // /**
  //  * シミュレータへ競技の終了を通知する
  //  */
  // void notifyCompletedToSimulator();

  void resetMotorCount();

 private:
  ev3api::Motor rightWheel;
  ev3api::Motor leftWheel;
  ev3api::Motor armMotor;
  ev3api::Clock clock;

  /**
   * モータに設定するPWM値の制限
   * @param value 入力されたPWM値
   * @return 制限されたPWM値
   */
  int limitPwmValue(const int value);
};

#endif
