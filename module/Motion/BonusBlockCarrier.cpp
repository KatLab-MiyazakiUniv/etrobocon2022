/**
 * @file BonusBlockCarrier.cpp
 * @brief ボーナスブロックをベースエリアまで運搬する
 * @author sugaken0528
 */

#include "BonusBlockCarrier.h"

void BonusBlockCarrier::carryBonusBlock()
{
  Rotation rotation;
  StraightRunner straightRunner;
  LineTracer lineTracer(true);

  int targetBrightness = (93 - 3) / 2;  // 目標輝度

  // 交点内を直進
  straightRunner.run(20);

  // 左に90度ピボットターン
  rotation.turnForwardLeftPivot(90, 70);

  // 赤を認識するまでライントレース
  lineTracer.runToColor(COLOR::RED, targetBrightness, 30, PidGain(0.1, 0.8, 0.12));

  // 交点内を直進
  straightRunner.run(20);

  // 左に90度ピボットターン
  rotation.turnForwardLeftPivot(90, 80);

  // 緑を認識するまで直進(指定した距離まで直進で代用)
  straightRunner.run(100, 30);

  // 緑を認識するまでライントレース
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, 30, PidGain(0.1, 0.8, 0.12));

  // 左に90度ピボットターン
  rotation.turnForwardLeftPivot(90, 70);
}