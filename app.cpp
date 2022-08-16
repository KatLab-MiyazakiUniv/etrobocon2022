/**
 * @file app.cpp
 * @brief タスクを管理するクラス
 * @author miyashita64
 */

#include "Measurer.h"
#include "Controller.h"
#include "EtRobocon2022.h"
#include "app.h"

// メインタスク
void main_task(intptr_t unused)
{
  EtRobocon2022::start();
  ext_tsk();
}

// アームを一定に保つタスク
void arm_task(intptr_t unused)
{
  // 角度を変えるために最低限必要なPWM値
  static constexpr int MIN_PWM = 15;

  Measurer measurer;
  Controller controller;

  // 0はRasPike起動時のアームの角度(モータの回転量)
  int maxCount = 0;
  int currentCount = measurer.getArmMotorCount();
  int prevCount = currentCount - 1;
  int pwm = 0;
  while(true) {
    // 現在のアームの角度を取得する
    currentCount = measurer.getArmMotorCount();

    // 回転量の最大値(最もアームが低い)を保持する
    if(maxCount < currentCount){
      maxCount = currentCount;
    }

    // アームが下がる(回転量が大きくなる)余地があれば調整する
    pwm = (currentCount > prevCount || maxCount > currentCount) ? MIN_PWM : 0;
    controller.setArmMotorPwm(pwm);

    prevCount = currentCount;
    controller.sleep();
  }
  ext_tsk();
}