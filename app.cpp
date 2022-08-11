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

// アームを水平に保つタスク
void arm_task(intptr_t unused)
{
  // 目標とするアームの角度（モータの回転量）
  static constexpr int TARGET_COUNT = 0;
  // 角度を変えるために最低限必要なPWM値
  static constexpr int MIN_PWM = 10;

  Measurer measurer;
  Controller controller;

  int currentCount = measurer.getArmMotorCount();
  int direction = 0;
  while(true) {
    // 現在のアームの角度を取得する
    currentCount = measurer.getArmMotorCount();
    // 調整の方向を判定する
    direction = currentCount < TARGET_COUNT ? 1 : currentCount > TARGET_COUNT ? -1 : 0;
    controller.setArmMotorPwm(MIN_PWM * direction);
    controller.sleep();
  }
  ext_tsk();
}