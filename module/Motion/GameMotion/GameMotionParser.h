/**
 * @file GameMotionParser.h
 * @brief ソースファイルをゲーム動作に解釈する
 * @author miyashita64, kawano
 */

#ifndef GAME_MOTION_PAESER_H
#define GAME_MOTION_PAESER_H

#include <stdio.h>

class GameMotionParser {
 public:
  static int parseGameMotionFile();

 private:
  static constexpr char* sourceFileName = "etrobocon2022/GameMotions.csv";
};

#endif