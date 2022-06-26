/**
 * @file StraightRunner.h
 * @brief 直進クラス
 * @author hiroto0927, miyashita64
 */

#ifndef STRAIGHTER_H
#define STRAIGHTER_H

#include "Measurer.h"
#include "Mileage.h"
#include "Controller.h"
#include "Pid.h"

class StraightRunner {
 public:
  /**
   * コンストラクタ
   */
  StraightRunner();

  /**
   * 指定された距離を直進する関数
   * @param targetDistance 目標距離
   * @param pwm PWM値
   */
  void runStraightToDistance(double targetDistance, int pwm);

 private:
  // SECTION_DISTANCE毎にACCELE_PWMだけPWM値を上げる
  static constexpr int SECTION_DISTANCE = 10;  // 調整距離[mm]
  static constexpr int ACCELE_PWM = 10;        // 追加のPWM値

  Measurer measurer;
  Controller controller;
};
#endif