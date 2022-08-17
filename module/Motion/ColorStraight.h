/**
 * @file   ColorStraight.h
 * @brief  指定色直進動作
 * @author sugaken0528 kawanoichi mutotaka0426
 */

#ifndef COLOR_STRAIGHT_H
#define COLOR_STRAIGHT_H

#include "Motion.h"
#include "Pid.h"
#include "ColorJudge.h"

class ColorStraight : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 指定色
   * @param _pwm PWM値 -100~100
   */
  ColorStraight(COLOR _targetColor, int _pwm);

  /**
   * @brief 指定色まで直進する
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  static constexpr double ACCELE_PWM = 0.3;  // 加速するPWM値
  static constexpr int MIN_PWM = 40;  // 静止時から走行体がモーターを動かせないPWM値
  COLOR targetColor;                  // 指定色
  int pwm;                            // PWM値 -100~100
};

#endif
