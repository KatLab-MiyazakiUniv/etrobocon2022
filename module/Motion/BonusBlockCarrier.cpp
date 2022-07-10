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
  Controller controller;

  int targetBrightness = (93 - 3) / 2;  // 目標輝度

  // 交点内を直進
  straightRunner.run(5, 50);

  // 左に90度ピボットターン
  rotation.turnForwardLeftPivot(89, 70);

  // 赤を認識するまでライントレース
  lineTracer.runToColor(COLOR::RED, targetBrightness, 40, PidGain(0.1, 0.08, 0.08));

  // 左に90度ピボットターン
  rotation.turnForwardLeftPivot(91, 87);

  // 直進を安定させるために1秒待機
  controller.sleep(1000000);

  // 緑を認識するまで直進(指定した距離まで直進で代用)
  straightRunner.run(400, 50);

  // 緑を認識するまでライントレース(指定した距離までライントレースで代用)
  lineTracer.run(240, targetBrightness, 53, PidGain(0.1, 0.08, 0.08));

  // 左に80度回頭
  rotation.rotateLeft(80, 70);

  // 後退
  straightRunner.run(20, -55);

  // 左に10度回頭
  rotation.rotateLeft(10, 80);

  // 後退
  straightRunner.run(40, -55);
}