/**
 * @file LineTraceArea.h
 * @brief ライントレースエリアを攻略するクラス
 * @author mutotaka0426 miyashita64
 */

#ifndef LINE_TRACE_AREA_H
#define LINE_TRACE_AREA_H

#include <stdio.h>
#include <string.h>
#include "LineTracer.h"
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
   * @param targetBrightness 目標輝度
   */
  static void runLineTraceArea(const bool isLeftCourse, bool& isLeftEdge,
                               const int targetBrightness);

 private:
  // データファイルのパス
  static constexpr char* leftSourceFileName = "etrobocon2022/datafiles/LineTraceLeftParams.csv";
  static constexpr char* rightSourceFileName = "etrobocon2022/datafiles/LineTraceRightParams.csv";

  LineTraceArea();  // インスタンス化を禁止する
};

#endif
