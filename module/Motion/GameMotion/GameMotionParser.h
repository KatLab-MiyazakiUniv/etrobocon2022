/**
 * @file GameMotionParser.h
 * @brief ソースファイルをゲーム動作に解釈する
 * @author miyashita64, kawano
 */

#ifndef GAME_MOTION_PAESER_H
#define GAME_MOTION_PAESER_H

#include <stdio.h>

/**
 ** @brief カメラシステムから送信されたファイルを読み込む
 ** @return 読み込みの成否を返す(0:成功, -1:失敗)
 **/
class GameMotionParser {
 public:
  static int readGameMotionFile();

 private:
  static constexpr char* sourceFileName = "etrobocon2022/transfer_data/GameMotions.txt";
};

#endif