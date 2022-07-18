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

  // 左に90度ピボットターン
  rotation.turnForwardLeftPivot(90, 70); //角度, PWM

  // エッジ変更 true:左エッジ, false:右エッジ
  lineTracer.setIsLeftEdge(false);

  // 赤を認識するまでライントレース
  lineTracer.runToColor(COLOR::RED, targetBrightness, 40, PidGain(0.1, 0.08, 0.08));

  // エッジ変更 true:左エッジ, false:右エッジ
  // lineTracer.setIsLeftEdge(true);

  // 左に90度ピボットターン
  rotation.turnForwardLeftPivot(91, 87);

  // 直進を安定させるために1秒待機
  controller.sleep(1000000);

  // 指定した色まで直進
  straightRunner.runStraightToColor(50, COLOR::GREEN);

  // 指定した距離(交点マーカーを通り過ぎる距離)を直進
  straightRunner.run(80, 50);

  lineTracer.run(100, targetBrightness, 50, PidGain(0.5, 0.08, 0.08));
  // // 指定した色までライントレース
  // lineTracer.runToColor(COLOR::GREEN, targetBrightness, 50, PidGain(0.5, 0.08, 0.08));

  // // 指定した距離(交点マーカーを通り過ぎる距離)を直進
  // straightRunner.run(80, 50);


  // /**
  //  * そのまま90度回頭して設置するとブロックがベースエリアからはみ出る場合があるため，
  //  * 回頭と後退を分けて実行する
  //  */
  // // 左に80度回頭
  // rotation.rotateLeft(80, 70);

  // // 後退
  // straightRunner.run(20, -55);

  // // 左に10度回頭
  // rotation.rotateLeft(10, 80);

  // // 後退
  // straightRunner.run(40, -55);
}