/**
 * @file LineTraceArea.h
 * @brief ライントレースエリアを攻略するクラス
 * @author mutotaka0426
 */

#ifndef LINE_TRACE_AREA_H
#define LINE_TRACE_AREA_H

#include <array>
#include "LineTracer.h"

//区間の情報を保持する構造体
struct SectionParam {
  double distance;       //走行距離
  int targetBrightness;  //目標輝度
  int pwm;               // PWM値
  PidGain pidGain;       // PIDゲイン
};

class LineTraceArea {
 public:
  /**
   * @fn static void runLineTraceArea();
   * @brief ライントレースエリアを走行する
   * @param isLeftCourse コースのLR判定(true:Lコース, false:Rコース)
   */
  static void runLineTraceArea(const bool isLeftCourse);

 private:
  static const int LEFT_SECTION_SIZE = 6;   // Lコースの区間の数
  static const int RIGHT_SECTION_SIZE = 6;  // Rコースの区間の数
  static const std::array<SectionParam, LEFT_SECTION_SIZE> LEFT_COURSE_INFO;  // Lコースの情報
  static const std::array<SectionParam, RIGHT_SECTION_SIZE> RIGHT_COURSE_INFO;  // Rコースの情報

  LineTraceArea();  // インスタンス化を禁止する
};

#endif
