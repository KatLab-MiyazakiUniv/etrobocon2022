/**
 * @file ColorBlockCarrier.cpp
 * @brief カラーブロックをベースエリアまで運搬する
 * @author sap2368
 */

#include "ColorBlockCarrier.h"

// Lコースの下のベースエリアへの設置処理のみ実装
// TODO: Lコース上左右, Rコース上下左右のベースエリアに設置する処理を追加する
void ColorBlockCarrier::run(int targetBrightness)
{
  Rotation rotation;
  StraightRunner straightRunner;
  LineTracer lineTracer(true);
  Controller controller;

  // 交点内を直進
  straightRunner.run(10, -50);

  // 緑を認識するまでライントレース
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, -40, PidGain(0.1, 0.08, 0.08));

  // // 右に45度回頭
  // rotation.rotateRight(45, 70);

  // // ブロックまで直進
  // straightRunner.run(34, 50);

  // // 右に45度回頭
  // rotation.rotateRight(45, 70);

  // // 黒線まで直進
  // straightRunner.run(24, 50);

  // // 右に90度回頭
  // rotation.rotateRight(90, 70);

  // // 黄色を認識するまでライントレース
  // lineTracer.runToColor(COLOR::YELLOW, targetBrightness, 40, PidGain(0.1, 0.08, 0.08));

  // // 交点内を直進
  // straightRunner.run(5, 50);

  // // 赤を認識するまでライントレース
  // lineTracer.runToColor(COLOR::RED, targetBrightness, 40, PidGain(0.1, 0.08, 0.08));

  // // 交点内を直進
  // straightRunner.run(5, 50);

  // // 赤を認識するまでライントレース
  // lineTracer.runToColor(COLOR::RED, targetBrightness, 40, PidGain(0.1, 0.08, 0.08));

  // // 交点内を直進
  // straightRunner.run(5, 50);
}