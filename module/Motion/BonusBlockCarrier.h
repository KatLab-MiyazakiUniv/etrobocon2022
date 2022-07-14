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
  /**
   * ベースエリアにボーナスブロックを運ぶ
   * @param targetBrightness 目標輝度
   */
  static void run(int targetBrightness);

 private:
  BonusBlockCarrier();  // インスタンス化を禁止する
};
#endif