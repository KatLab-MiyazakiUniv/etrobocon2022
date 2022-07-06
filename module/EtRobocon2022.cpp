/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555 mutotaka0426
 */

#include "EtRobocon2022.h"
#include "LineTraceArea.h"
#include "Calibrator.h"

void EtRobocon2022::start()
{
  bool isLeftCourse = true;
  int targetBrightness = (93 + 3) / 2;
  Calibrator calibrator;

  // キャリブレーションする
  calibrator.run();
  isLeftCourse = calibrator.getIsLeftCourse();
  targetBrightness = calibrator.getTargetBrightness();

  // 合図を送るまで待機する
  calibrator.waitForStart();

  // ライントレースエリアを走行する
  LineTraceArea::runLineTraceArea(isLeftCourse, targetBrightness);
}
