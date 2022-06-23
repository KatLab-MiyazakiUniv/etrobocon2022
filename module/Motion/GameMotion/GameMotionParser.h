/**
 * @file GameMotionParser.h
 * @brief ソースファイルをゲーム動作に解釈する
 * @author miyashita64, kawano
 */

#ifndef GAME_MOTION_PAESER_H
#define GAME_MOTION_PAESER_H

#include <stdio.h>
#include <fstream>
#include <string>

class GameMotionParser {
 public:
  static int parseGameMotionFile();

 private:
  static constexpr char* sourceFileName = "data/GameMotions.csv";
};

#endif
