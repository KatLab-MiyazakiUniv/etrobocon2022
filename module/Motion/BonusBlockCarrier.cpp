/**
 * @file BonusBlockCarrier.cpp
 * @brief ボーナスブロックをベースエリアまで運搬する
 * @author sugaken0528 kawanoichi
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

  // 左に90度ピボットターン
  rotation.turnForwardLeftPivot(89, 70);  //角度, PWM

  // エッジ変更 true:左エッジ, false:右エッジ
  lineTracer.setIsLeftEdge(false);

  // 赤(端点サークル)を認識するまでライントレース
  lineTracer.runToColor(COLOR::RED, targetBrightness, 40, PidGain(0.1, 0.08, 0.08));

  // 左に90度ピボットターン
  rotation.turnForwardLeftPivot(89, 85);

  // 直進を安定させるために1秒待機
  controller.sleep(100000);

  // 緑の交点マーカー(右下)まで直進
  straightRunner.runToColor(COLOR::GREEN, 50);

  // 直進(交点マーカーを通り過ぎる)
  straightRunner.run(70, 50);

  // 緑の交点マーカー(左下)までライントレース
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, 50, PidGain(0.5, 0.08, 0.08));

  // 直進(交点マーカーを通り過ぎる)
  straightRunner.run(80, 50);

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