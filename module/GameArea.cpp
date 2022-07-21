/**
 * @file GameArea.cpp
 * @brief ゲームエリアを攻略するクラス
 * @author kawanoichi
 */

#include "GameArea.h"

void GameArea::runGameArea(const bool isLeftCourse, const int targetBrightness)
{
  bool isLeftEdge;  // true:左エッジ, false:右エッジ

  // エッジをセット
  isLeftEdge = isLeftCourse;

  // LineTracerにエッジを与えてインスタンス化する
  LineTracer lineTracer(isLeftEdge);

  // Linetracer::runに区間の情報を渡して走行させる (第1引数: 距離 + 調整距離(300+120))
  lineTracer.run(420, targetBrightness, 50, PidGain(1.0, 1.1, 1.0));

  // Linetracer::runに区間の情報を渡して走行させる (第1引数: 距離 + 調整距離(485+0))
  lineTracer.run(485, targetBrightness, 50, PidGain(0.6, 0.8, 0.8));

  // Linetracer::runに区間の情報を渡して走行させる (第1引数: 距離 + 調整距離(485+0))
  lineTracer.run(1025, targetBrightness, 50, PidGain(0.8, 0.8, 0.8));

  // 緑までライントレース
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, 40, PidGain(1.0, 1.0, 1.0));

  // ベースエリアにボーナスブロックを運ぶ
  BonusBlockCarrier::run(targetBrightness);
}
