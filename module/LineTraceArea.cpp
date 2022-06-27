/**
 * @file LineTraceArea.cpp
 * @brief ライントレースエリアを攻略するクラス
 * @author mutotaka0426
 */

#include "LineTraceArea.h"
#include "Controller.h"  // テスト用に書いたやつだから消し忘れるなよ
using namespace std;

// Lコースの情報を初期化する
const array<SectionParam, LineTraceArea::LEFT_SECTION_SIZE> LineTraceArea::LEFT_COURSE_INFO
    = { SectionParam{ 1070 + 30, 45, 50, PidGain(0.2, 0.8, 0.1) },
        SectionParam{ 212 + 120, 45, 50, PidGain(1.2, 1.0, 1.0) },
        SectionParam{ 1830, 45, 50, PidGain(1.0, 1.0, 1.0) },
        SectionParam{ 190 + 120, 45, 50, PidGain(1.2, 1.0, 1.0) },
        SectionParam{ 1100, 45, 50, PidGain(1.0, 0.8, 0.8) },
        SectionParam{ 485 + 250, 45, 50, PidGain(1.2, 0.8, 0.8) } };

// Rコースの情報を初期化する
const array<SectionParam, LineTraceArea::RIGHT_SECTION_SIZE> LineTraceArea::RIGHT_COURSE_INFO
    = { SectionParam{ 1070 + 30, 45, 50, PidGain(0.2, 0.8, 0.1) },
        SectionParam{ 212 + 120, 45, 50, PidGain(1.2, 1.0, 1.0) },
        SectionParam{ 1830, 45, 50, PidGain(1.0, 1.0, 1.0) },
        SectionParam{ 190 + 120, 45, 50, PidGain(1.2, 1.0, 1.0) },
        SectionParam{ 1100, 45, 50, PidGain(1.0, 0.8, 0.8) },
        SectionParam{ 485 + 250, 45, 50, PidGain(1.2, 0.8, 0.8) } };

void LineTraceArea::runLineTraceArea(const bool isLeftCourse)
{
  const SectionParam* param;
  bool isLeftEdge;  // true:左エッジ, false:右エッジ

  // Lコースの場合
  param = LEFT_COURSE_INFO.begin();
  // エッジをセット
  isLeftEdge = isLeftCourse;
  // LineTracerにエッジを与えてインスタンス化する
  LineTracer lineTracer(isLeftEdge);

  Controller controller;  // テスト用に書いたやつだから消し忘れるなよ

  // LRに応じて各区間を順番に走らせる
  for(int i = 0; i < LEFT_SECTION_SIZE; i++) {
    // for(int i = 0; i < 4; i++) {
    SectionParam section = param[i];
    // Linetracerクラスのrun関数に区間の情報を渡して走行させる
    lineTracer.run(section.distance, section.targetBrightness, section.pwm, section.pidGain);
  }

  // 緑までライントレース
  lineTracer.runToColor(COLOR::GREEN, 45, 50, PidGain{ 1.0, 1.0, 1.0 });
}
