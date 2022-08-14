/**
 * @file   StraightRunnerDistance.h
 * @brief  指定距離直進動作
 * @author sugaken0528 kawanoichi mutotaka0426
 */

#ifndef STRAIGHT_RUNNER_DISTANCE_H
#define STRALINE_TRACER_DISTANCE_H

#include "Motion.h"
#include "Pid.h"
#include "Mileage.h"

class StraightRunnerDistance : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 目標距離 0~∞
   * @param _pwm PWM値 -100~100
   */
  StraightRunnerDistance(double _targetDistance, int _pwm);

  /**
   * @brief 指定距離だけ直進する
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
  double targetDistance;              // 目標距離 0~∞
  int pwm;                            // PWM値 -100~100
};

#endif
