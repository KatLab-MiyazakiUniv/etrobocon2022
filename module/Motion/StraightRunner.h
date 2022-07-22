/**
 * @file StraightRunner.h
 * @brief 直進クラス
 * @author sugaken0528 kawanoichi
 */

#ifndef STRAIGHTER_H
#define STRAIGHTER_H

#include "Measurer.h"
#include "Mileage.h"
#include "Controller.h"
#include "Logger.h"
#include "Pid.h"
#include "ColorJudge.h"

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
  void run(double targetDistance, int pwm);

  /**
   * 指定した色を検出するまで直進する
   * @param targetColor 目標色
   * @param pwm PWM値
   */
  void runToColor(COLOR targetColor, int pwm);

 private:
  // SECTION_DISTANCE毎にACCELE_PWMだけPWM値を上げる
  static constexpr double ACCELE_PWM = 0.3;  // 追加のPWM値
  static constexpr int MIN_PWM = 40;  // 静止時から走行体がモーターを動かせないPWM値

  Measurer measurer;
  Controller controller;
  Logger logger;
};
#endif