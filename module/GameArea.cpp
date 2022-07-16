/**
 * @file GameArea.cpp
 * @brief ゲームエリアを攻略するクラス
 * @author kawano
 */

#include "GameArea.h"

void GameArea::runGameArea()
{
  //ベースエリアにボーナスブロックを運ぶ
  BonusBlockCarrier::run();
}
