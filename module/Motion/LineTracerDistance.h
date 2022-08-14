/**
 * @file   LineTracerDistance.h
 * @brief  指定距離ライントレース動作
 * @author mutotaka0426 kodama0720
 */

#ifndef LINE_TRACER_DISTANCE_H
#define LINE_TRACER_DISTANCE_H

#include "Motion.h"
#include "Pid.h"
#include "Mileage.h"

class LineTracerDistance : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 目標距離 0~∞
   * @param _targetBrightness 目標輝度
   * @param _pwm PWM値 -100~100
   * @param _gain PIDゲイン
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   */
  LineTracerDistance(double _targetDistance, int _targetBrightness, int _pwm, const PidGain& _gain,
                     bool& _isLeftEdge);

  /**
   * @brief 指定距離だけライントレースする
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  double targetDistance;    // 目標距離 0~∞
  double targetBrightness;  // 目標輝度
  int pwm;                  // PWM値 -100~100
  PidGain gain;             // PIDゲイン
  bool& isLeftEdge;         // エッジの左右判定(true:左エッジ, false:右エッジ)
};

#endif
