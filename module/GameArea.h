/**
 * @file GameArea.h
 * @brief ゲームエリアを攻略するクラス
 * @author kawanoichi
 */

#ifndef GAME_AREA_H
#define GAME_AREA_H

#include "BonusBlockCarrier.h"
#include "LineTracer.h"

class GameArea {
 public:
  /**
   * @brief ゲームエリアを攻略する
   * @param isLeftCourse コースのLR判定(true:Lコース, false:Rコース)
   * @param targetBrightness 目標輝度
   */
  static void runGameArea(const bool isLeftCourse, const int targetBrightness);

 private:
  GameArea();  // インスタンス化を禁止する
};

#endif