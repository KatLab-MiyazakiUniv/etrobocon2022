/**
 * @file BonusBlockCarrier.h
 * @brief ボーナスブロックをベースエリアまで運搬する
 * @author sugaken0528
 */

#ifndef BONUS_BLOCK_CARRIER_H
#define BONUS_BLOCK_CARRIER_H

#include "Rotation.h"
#include "LineTracer.h"
#include "StraightRunner.h"
#include "Controller.h"

class BonusBlockCarrier {
 public:
  static void carryBonusBlock();
};
#endif