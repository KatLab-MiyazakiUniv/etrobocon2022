/**
 * @file   MotionParser.h
 * @brief  動作コマンドファイルを解析するクラス
 * @author mutotaka0426 miyashita64
 */

#ifndef MOTION_PARSER_H
#define MOTION_PARSER_H

#include <vector>
#include <stdio.h>
#include <string.h>
#include "Logger.h"
#include "Motion.h"
#include "DistanceLineTracing.h"
#include "ColorLineTracing.h"
#include "DistanceStraight.h"
#include "ColorStraight.h"
#include "Rotation.h"
#include "DistanceTurning.h"
#include "EdgeChanging.h"
#include "Sleeping.h"

enum class COMMAND {
  DL,  // 指定距離ライントレース
  CL,  // 指定色ライントレース
  DS,  // 指定距離直進
  CS,  // 指定色直進
  RT,  // 回頭
  DT,  // 旋回
  EC,  // エッジ切り替え
  SL,  // 自タスクスリープ
  NONE
};

class MotionParser {
 public:
  /**
   * @brief ファイルを解析して動作インスタンスのリストを生成する
   * @param filePath ファイルパス
   * @param targetBrightness 目標輝度
   * @param isLeftEdge エッジのLR判定(true:Lコース, false:Rコース)
   * @return 動作インスタンスリスト
   */
  static std::vector<Motion*> createMotions(const char* filePath, int targetBrightness,
                                            bool& isLeftEdge);

 private:
  MotionParser();  // インスタンス化を禁止する

  /**
   * @brief 文字列を列挙型COMMANDに変換する
   * @param str 文字列のコマンド
   * @return コマンド
   */
  static COMMAND convertCommand(char* str);

  /**
   * @brief 文字列をbool型に変換する
   * @param str 文字列のbool値
   * @return bool値
   */
  static bool convertBool(char* str);
};

#endif