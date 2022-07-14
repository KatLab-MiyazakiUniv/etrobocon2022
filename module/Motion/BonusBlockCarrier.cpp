/**
 * @file BonusBlockCarrier.cpp
 * @brief ボーナスブロックをベースエリアまで運搬する
 * @author sugaken0528
 */

#include "BonusBlockCarrier.h"

// Lコースの下のベースエリアへの設置処理のみ実装
// TODO: Lコース上左右, Rコース上下左右のベースエリアに設置する処理を追加する
void BonusBlockCarrier::run(int targetBrightness)
{
  Rotation rotation;
  StraightRunner straightRunner;
  LineTracer lineTracer(true);
  Controller controller;

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

  // 緑を認識するまで直進
  // TODO: 指定した距離まで直進で代用してるので，指定した色まで直進に変更する
  straightRunner.run(400, 50);

  // 緑を認識するまでライントレース
  // TODO: 指定した距離までライントレースで代用してるので，指定した色までライントレースに変更する
  lineTracer.run(240, targetBrightness, 53, PidGain(0.1, 0.08, 0.08));

  /**
   * そのまま90度回頭して設置するとブロックがベースエリアからはみ出る場合があるため，
   * 回頭と後退を分けて実行する
   */
  // 左に80度回頭
  rotation.rotateLeft(80, 70);

  // 後退
  straightRunner.run(20, -55);

  // 左に10度回頭
  rotation.rotateLeft(10, 80);

  // 後退
  straightRunner.run(40, -55);
}