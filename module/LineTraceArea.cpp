/**
 * @file LineTraceArea.cpp
 * @brief ライントレースエリアを攻略するクラス
 * @author mutotaka0426 kawanoichi
 */

#include "LineTraceArea.h"
using namespace std;

const array<double, LineTraceArea::LEFT_SECTION_SIZE> LineTraceArea::LEFT_SECTION_DISTANCE
    = { 1070, 212, 1830, 190, 800};

const array<double, LineTraceArea::RIGHT_SECTION_SIZE> LineTraceArea::RIGHT_SECTION_DISTANCE
    = { 1070, 212, 1830, 190, 800};

// Lコースのパラメータを初期化する（調整距離, PWM値, PIDゲイン）
const array<SectionParam, LineTraceArea::LEFT_SECTION_SIZE> LineTraceArea::LEFT_COURSE_INFO = {
  SectionParam{ 30, 50, PidGain(0.2, 0.8, 0.1) }, SectionParam{ 100, 40, PidGain(1.1, 1.0, 0.5) },
  SectionParam{ -100, 50, PidGain(1.0, 1.0, 1.0) }, SectionParam{ 160, 50, PidGain(1.1, 1.0, 1.0) },
  SectionParam{ -10, 50, PidGain(1.0, 0.8, 0.8) }
};

// Rコースのパラメータを初期化する（調整距離, PWM値, PIDゲイン）
const array<SectionParam, LineTraceArea::RIGHT_SECTION_SIZE> LineTraceArea::RIGHT_COURSE_INFO = {
  SectionParam{ 30, 50, PidGain(0.2, 0.8, 0.1) }, SectionParam{ 120, 50, PidGain(1.2, 1.0, 1.0) },
  SectionParam{ 0, 50, PidGain(1.0, 1.0, 1.0) }, SectionParam{ 120, 50, PidGain(1.2, 1.0, 1.0) },
  SectionParam{ 0, 50, PidGain(1.0, 0.8, 0.8) }
};

void LineTraceArea::runLineTraceArea(const bool isLeftCourse, const int targetBrightness)
{
  int size;                   // 区間の数
  const double* DISTANCE;     // 各区間の距離
  const SectionParam* PARAM;  // ファイルから受け取ったパラメータ
  bool isLeftEdge;            // true:左エッジ, false:右エッジ
  char buf[50];               // log用にメッセージを一時保存する
  Logger logger;

  if(isLeftCourse) {  // Lコースの場合
    size = LEFT_SECTION_SIZE;
    DISTANCE = LEFT_SECTION_DISTANCE.begin();
    PARAM = LEFT_COURSE_INFO.begin();
  } else {  // Rコースの場合
    size = RIGHT_SECTION_SIZE;
    DISTANCE = RIGHT_SECTION_DISTANCE.begin();
    PARAM = RIGHT_COURSE_INFO.begin();
  }

  // エッジをセット
  isLeftEdge = isLeftCourse;

  // LineTracerにエッジを与えてインスタンス化する
  LineTracer lineTracer(isLeftEdge);

  const char* course = isLeftCourse ? "Left" : "Right";
  sprintf(buf, "\nRun on the %s Course\n", course);
  logger.logHighlight(buf);
  Controller controller;
  for(int i = 0; i < size; i++) {
    // Linetracer::runに区間の情報を渡して走行させる
    lineTracer.run(DISTANCE[i] + PARAM[i].tweak, targetBrightness, PARAM[i].pwm, PARAM[i].pidGain);
    // controller.sleep(1000000);
  }
}
