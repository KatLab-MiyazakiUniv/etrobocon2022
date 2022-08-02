/**
 * @file LineTraceArea.h
 * @brief ライントレースエリアを攻略するクラス
 * @author mutotaka0426
 */

#ifndef LINE_TRACE_AREA_H
#define LINE_TRACE_AREA_H

#include <array>
#include <string>
#include "LineTracer.h"
#include "Logger.h"
#include "Controller.h"

// 区間制御のパラメータを保持する構造体
struct SectionParam {
  double tweak;     // 調整距離
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
  static void runLineTraceArea(const bool isLeftCourse, const int targetBrightness);

 private:
  static constexpr int LEFT_SECTION_SIZE = 5;   // Lコースの区間の数
  static constexpr int RIGHT_SECTION_SIZE = 5;  // Rコースの区間の数
  // Lコースの各区間の距離
  static const std::array<double, LEFT_SECTION_SIZE> LEFT_SECTION_DISTANCE;
  // Rコースの各区間の距離
  static const std::array<double, LEFT_SECTION_SIZE> RIGHT_SECTION_DISTANCE;

  // TODO: 以下の2つの定数はファイル読み込みに置き換える
  static const std::array<SectionParam, LEFT_SECTION_SIZE> LEFT_COURSE_INFO;  // Lコースの情報
  static const std::array<SectionParam, RIGHT_SECTION_SIZE> RIGHT_COURSE_INFO;  // Rコースの情報

  LineTraceArea();  // インスタンス化を禁止する
};

#endif
