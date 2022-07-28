/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555 mutotaka0426 kawanoichi
 */

#include "EtRobocon2022.h"
#include "Calibrator.h"
#include "LineTraceArea.h"
#include "GameArea.h"

void EtRobocon2022::start()
{
  bool isLeftCourse = true;
  bool isLeftEdge = true;
  int targetBrightness = (WHITE_BRIGHTNESS + BLACK_BRIGHTNESS) / 2;
  Calibrator calibrator;

  // キャリブレーションする
  calibrator.run();
  isLeftCourse = calibrator.getIsLeftCourse();
  isLeftEdge = isLeftCourse;
  targetBrightness = calibrator.getTargetBrightness();

  // 合図を送るまで待機する
  calibrator.waitForStart();

  // ライントレースエリアを走行する
  LineTraceArea::runLineTraceArea(isLeftCourse, isLeftEdge, targetBrightness);

  // ゲームエリアを攻略する
  GameArea::runGameArea(isLeftEdge, targetBrightness);
}
