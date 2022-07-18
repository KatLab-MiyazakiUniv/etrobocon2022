/**
 * @file ColorBlockCarrier.h
 * @brief カラーブロックをベースエリアまで運搬する
 * @author sap2368
 */

#ifndef COLOR_BLOCK_CARRIER_H
#define COLOR_BLOCK_CARRIER_H

#include "Rotation.h"
#include "LineTracer.h"
#include "StraightRunner.h"
#include "Controller.h"

class ColorBlockCarrier {
 public:
  /**
   * ベースエリアにカラーブロックを運ぶ
   * @param targetBrightness 目標輝度
   */
  static void run(int targetBrightness);

 private:
  ColorBlockCarrier();  // インスタンス化を禁止する
};
#endif