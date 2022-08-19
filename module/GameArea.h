/**
 * @file   GameArea.h
 * @brief  ゲームエリアを攻略するクラス
 * @author kawanoichi kodama0720 mutotaka0426
 */

#ifndef GAME_AREA_H
#define GAME_AREA_H

#include <vector>
#include "MotionParser.h"
#include "Logger.h"

class GameArea {
 public:
  /**
   * @brief ゲームエリアを攻略する
   * @param isLeftCourse コースのLR判定(true:Lコース, false:Rコース)
   * @param isLeftEdge エッジのLR判定(true:Lコース, false:Rコース)
   * @param targetBrightness 目標輝度
   */
  static void runGameArea(const bool isLeftCourse, bool& isLeftEdge, const int targetBrightness);

 private:
  // 端点サークルまでのコマンドファイルのパス
  static constexpr char* toEndPointLeft = "etrobocon2022/datafiles/ToEndPointLeft.csv";
  static constexpr char* toEndPointRight = "etrobocon2022/datafiles/ToEndPointRight.csv";
  // ゲームエリアのコマンドファイルのパス
  static constexpr char* gameAreaLeft = "etrobocon2022/datafiles/Game_Left_02_0818.csv";
  static constexpr char* gameAreaRight = "etrobocon2022/datafiles/Game_Right_02_0818.csv";

  GameArea();  // インスタンス化を禁止する
};

#endif
