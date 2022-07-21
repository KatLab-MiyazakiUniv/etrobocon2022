/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555 mutotaka0426 kawaichi
 */

#include "EtRobocon2022.h"
#include "Calibrator.h"
#include "LineTraceArea.h"
#include "GameArea.h"

void EtRobocon2022::start()
{
  bool isLeftCourse = true;
  int targetBrightness = (WHITE_BRIGHTNESS + BLACK_BRIGHTNESS) / 2;
  Calibrator calibrator;

  // キャリブレーションする
  calibrator.run();
  isLeftCourse = calibrator.getIsLeftCourse();
  targetBrightness = calibrator.getTargetBrightness();

  // 合図を送るまで待機する
  calibrator.waitForStart();

  // ライントレースエリアを走行する
  LineTraceArea::runLineTraceArea(isLeftCourse, targetBrightness);

  // ゲームエリアを攻略する
  GameArea::runGameArea(isLeftCourse, targetBrightness);
}
