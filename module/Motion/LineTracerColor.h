/**
 * @file   LineTracerColor.h
 * @brief  指定色ライントレース動作
 * @author mutotaka0426 kodama0720
 */

#ifndef LINE_TRACER_COLOR_H
#define LINE_TRACER_COLOR_H

#include "Motion.h"
#include "Pid.h"
#include "ColorJudge.h"

class LineTracerColor : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 指定色
   * @param _targetBrightness 目標輝度
   * @param _pwm PWM値 -100~100
   * @param _gain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   */
  LineTracerColor(COLOR _targetColor, int _targetBrightness, int _pwm, const PidGain& _gain,
                  bool& _isLeftEdge);

  /**
   * @brief 指定色までライントレースする
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  static constexpr int JUDGE_COUNT = 3;
  COLOR targetColor;        // 指定色
  double targetBrightness;  // 目標輝度
  int pwm;                  // PWM値 -100~100
  PidGain gain;             // PIDゲイン
  bool& isLeftEdge;         // エッジの左右判定(true:左エッジ, false:右エッジ)
};

#endif
