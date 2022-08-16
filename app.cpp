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
  static constexpr int MIN_PWM = 12;

  Measurer measurer;
  Controller controller;

  // 0はRasPike起動時のアームの角度（モータの回転量）
  int maxCount = 0;
  int currentCount = measurer.getArmMotorCount();
  int prevCount = currentCount;
  int direction = 0;
  while(true) {
    printf("current count: %d\n", currentCount);
    // 現在のアームの角度を取得する
    currentCount = measurer.getArmMotorCount();

    // 最大の回転量を目標とする
    if(maxCount < currentCount){
      maxCount = currentCount;
    }

    // アームが下がる(回転量が大きくなる)余地があれば調整する
    direction = currentCount > prevCount || maxCount > currentCount ? 1 : 0;
    controller.setArmMotorPwm(MIN_PWM * direction);
    controller.sleep();
  }
  ext_tsk();
}