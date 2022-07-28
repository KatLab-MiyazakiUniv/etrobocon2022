/**
 * @file GameArea.cpp
 * @brief ゲームエリアを攻略するクラス
 * @author kawanoichi kodama0720
 */

#include "GameArea.h"

void GameArea::runGameArea(const bool isLeftCourse, bool& isLeftEdge, const int targetBrightness)
{
  // インスタンス化
  LineTracer lineTracer(isLeftEdge);

  // 青までライントレース
  lineTracer.runToColor(COLOR::BLUE, targetBrightness, 40, PidGain(0.6, 0.8, 0.8));

  // 青ライン上をライントレース
  lineTracer.run(150, targetBrightness + 10, 50, PidGain(0.6, 0.8, 0.8));

  // カーブ
  lineTracer.run(400, targetBrightness, 45, PidGain(0.6, 0.8, 0.8));

  // 青までライントレース
  lineTracer.runToColor(COLOR::BLUE, targetBrightness, 40, PidGain(0.6, 0.8, 0.8));

  // 青ライン上をライントレース
  lineTracer.run(150, targetBrightness + 10, 50, PidGain(0.8, 0.8, 0.8));

  // 緑までライントレース
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, 50, PidGain(0.4, 0.8, 0.08));

  // ベースエリアにボーナスブロックを運ぶ
  BonusBlockCarrier::run(isLeftEdge, targetBrightness);
}
