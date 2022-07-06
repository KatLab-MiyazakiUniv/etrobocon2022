/**
 * @file LineTraceArea.cpp
 * @brief ライントレースエリアを攻略するクラス
 * @author mutotaka0426
 */

#include "LineTraceArea.h"
using namespace std;

const array<double, LineTraceArea::LEFT_SECTION_SIZE> LineTraceArea::LEFT_SECTION_DISTANCE
    = { 1070, 212, 1830, 190, 1100, 485 };

const array<double, LineTraceArea::RIGHT_SECTION_SIZE> LineTraceArea::RIGHT_SECTION_DISTANCE
    = { 1070, 212, 1830, 190, 1100, 485 };

// Lコースのパラメータを初期化する（調整距離, PWM値, PIDゲイン）
const array<SectionParam, LineTraceArea::LEFT_SECTION_SIZE + 1> LineTraceArea::LEFT_COURSE_INFO = {
  SectionParam{ 30, 50, PidGain(0.2, 0.8, 0.1) }, SectionParam{ 120, 50, PidGain(1.2, 1.0, 1.0) },
  SectionParam{ 0, 50, PidGain(1.0, 1.0, 1.0) },  SectionParam{ 120, 50, PidGain(1.2, 1.0, 1.0) },
  SectionParam{ 0, 50, PidGain(1.0, 0.8, 0.8) },  SectionParam{ 250, 50, PidGain(1.2, 0.8, 0.8) },
  SectionParam{ 0, 50, PidGain(1.0, 1.0, 1.0) }
};

// Rコースのパラメータを初期化する（調整距離, PWM値, PIDゲイン）
const array<SectionParam, LineTraceArea::RIGHT_SECTION_SIZE + 1> LineTraceArea::RIGHT_COURSE_INFO
    = { SectionParam{ 30, 50, PidGain(0.2, 0.8, 0.1) },
        SectionParam{ 120, 50, PidGain(1.2, 1.0, 1.0) },
        SectionParam{ 0, 50, PidGain(1.0, 1.0, 1.0) },
        SectionParam{ 120, 50, PidGain(1.2, 1.0, 1.0) },
        SectionParam{ 0, 50, PidGain(1.0, 0.8, 0.8) },
        SectionParam{ 250, 50, PidGain(1.2, 0.8, 0.8) },
        SectionParam{ 0, 50, PidGain(1.0, 1.0, 1.0) } };

void LineTraceArea::runLineTraceArea(const bool isLeftCourse, const int targetBrightness)
{
  int size;                   // 区間の数
  const double* DISTANCE;     // 各区間の距離
  const SectionParam* PARAM;  // ファイルから受け取ったパラメータ
  bool isLeftEdge;            // true:左エッジ, false:右エッジ

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

  string course = isLeftCourse ? "Left" : "Right";
  printf("\x1b[32m");  // 文字色を緑に
  printf("\nRun on the %s Course\n", course.c_str());
  printf("\x1b[39m\n");  // 文字色をデフォルトに戻す
  // LRに応じて各区間を順番に走らせる
  for(int i = 0; i < size; i++) {
    // Linetracer::runに区間の情報を渡して走行させる
    lineTracer.run(DISTANCE[i] + PARAM[i].tweak, targetBrightness, PARAM[i].pwm, PARAM[i].pidGain);
  }

  // 緑までライントレース
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, PARAM[size].pwm, PARAM[size].pidGain);
}
