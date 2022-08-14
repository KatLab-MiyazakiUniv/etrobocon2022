/**
 * @file   StraightRunnerColor.h
 * @brief  指定色直進動作
 * @author sugaken0528 kawanoichi mutotaka0426
 */

#ifndef STRAIGHT_RUNNER_COLOR_H
#define STRALINE_TRACER_COLOR_H

#include "Motion.h"
#include "Pid.h"
#include "ColorJudge.h"

class StraightRunnerColor : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 指定色
   * @param _pwm PWM値 -100~100
   */
  StraightRunnerColor(COLOR _targetColor, int _pwm);

  /**
   * @brief 指定色まで直進する
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  // SECTION_DISTANCE毎にACCELE_PWMだけPWM値を上げる
  static constexpr double ACCELE_PWM = 0.3;  // 追加のPWM値
  static constexpr int MIN_PWM = 40;  // 静止時から走行体がモーターを動かせないPWM値
  COLOR targetColor;                  // 指定色
  int pwm;                            // PWM値 -100~100
};

#endif
