/**
 * @file ColorBlockCarrier.cpp
 * @brief カラーブロックをベースエリアまで運搬する
 * @author sap2368
 */

#include "ColorBlockCarrier.h"

// Lコースの下のベースエリアへの設置処理のみ実装
void ColorBlockCarrier::run(int targetBrightness)
{
  Rotation rotation;
  StraightRunner straightRunner;
  LineTracer lineTracer(true);
  Controller controller;

  // // 交点内を直進
  // straightRunner.run(40, -50);

  // 緑を認識するまでライントレース
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, -40, PidGain(0.1, 0.08, 0.08));

  // 右に38度回頭
  rotation.rotateRight(38, 70);

  // ブロックまで直進
  straightRunner.run(145, 60);

  // 右に52度回頭
  rotation.rotateRight(52, 70);

  // 黒線まで直進
  straightRunner.run(152, 60);

  // 右に90度回頭
  rotation.rotateRight(90, 70);

  // 直進を安定させるために1秒待機
  controller.sleep(1000000);

  // 黄色を認識するまでライントレース
  lineTracer.runToColor(COLOR::YELLOW, targetBrightness, 50, PidGain(0.1, 0.08, 0.08));

  // 交点内を直進
  straightRunner.run(35, 70);

  // 赤を認識するまでライントレース
  lineTracer.runToColor(COLOR::RED, targetBrightness, 50, PidGain(0.1, 0.08, 0.08));

  // 交点内を直進
  straightRunner.run(80, 70);

  // 赤を認識するまでライントレース
  lineTracer.runToColor(COLOR::RED, targetBrightness, 50, PidGain(0.1, 0.08, 0.08));

  // 交点内を直進
  straightRunner.run(35, 70);
}