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
  /**
   ** @brief カメラシステムから送信されたファイルを読み込む
   ** @return 読み込みの成否を返す(0:成功, -1:失敗)
   **/
  static int readGameMotionFile();

 private:
  //  データファイルのパス
  static constexpr char* sourceFileName = "etrobocon2022/transfer_data/GameMotions.txt";
  // インスタンス化を禁止する
  GameMotionParser();
};

#endif