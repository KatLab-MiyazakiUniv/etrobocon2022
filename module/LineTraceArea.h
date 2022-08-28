/**
 * @file   LineTraceArea.h
 * @brief  ライントレースエリアを攻略するクラス
 * @author mutotaka0426 miyashita64
 */

#ifndef LINE_TRACE_AREA_H
#define LINE_TRACE_AREA_H

#include <vector>
#include <stdio.h>
#include <string.h>
#include "MotionParser.h"
#include "Logger.h"

// 区間制御のパラメータを保持する構造体
struct SectionParam {
  double distance;  // 距離
  int pwm;          // PWM値
  PidGain pidGain;  // PIDゲイン
};

class LineTraceArea {
 public:
  /**
   * @brief ライントレースエリアを走行する
   * @param isLeftCourse コースのLR判定(true:Lコース, false:Rコース)
   * @param isLeftEdge エッジのLR判定(true:Lコース, false:Rコース)
   * @param targetBrightness 目標輝度
   */
  static void runLineTraceArea(const bool isLeftCourse, bool& isLeftEdge,
                               const int targetBrightness);

 private:
  // ライントレースエリアのコマンドファイルのパス
  static constexpr char* lineTraceAreaLeft
      = "etrobocon2022/datafiles/Linetrace_Left_02_02_0819.csv";
  static constexpr char* lineTraceAreaRight
      = "etrobocon2022/datafiles/Linetrace_Right_02_02_0819.csv";

  LineTraceArea();  // インスタンス化を禁止する
};

#endif
