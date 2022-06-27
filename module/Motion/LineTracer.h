/**
 * @file LineTracer.h
 * @brief ライントレースをするクラス
 * @author mutotaka0426
 */

#ifndef LINE_TRACER_H
#define LINE_TRACER_H

#include <stdio.h>
#include <algorithm>
#include "Pid.h"
#include "Mileage.h"
#include "ColorJudge.h"
#include "Controller.h"
#include "Measurer.h"

class LineTracer {
 public:
  /**
   * コンストラクタ
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   */
  LineTracer(bool _isLeftEdge);

  /**
   * 指定された距離の間ライントレースをする
   * @param targetDistance 目標距離
   * @param targetBrightness 目標輝度
   * @param pwm PWM値
   * @param gain PIDゲイン
   */
  void run(double targetDistance, int targetBrightness, int pwm, const PidGain& gain);

  /**
   * 指定された色を判定するまでライントレースをする
   * @param targetColor 指定色
   * @param targetBrightness 目標輝度
   * @param pwm PWM値
   * @param gain PIDゲイン
   */
  void runToColor(COLOR targetColor, int targetBrightness, int pwm, const PidGain& gain);

  /**
   * エッジのゲッター
   * @return true: 左エッジ, false: 右エッジ
   */
  bool getIsLeftEdge();

  /**
   * エッジのセッター
   * @param _isLeftEdge true: 左エッジ, false: 右エッジ
   */
  void setIsLeftEdge(bool _isLeftEdge);

  /**
   * エッジを切り替える
   */
  void toggleEdge();

 private:
  bool isLeftEdge;
  Measurer measurer;
  Controller controller;
};

#endif
