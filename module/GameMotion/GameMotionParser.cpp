/**
 * @file GameMotionParser.cpp
 * @brief ソースファイルをゲーム動作に解釈する
 * @author miyashita64, kawano
 */

#include "GameMotionParser.h"

// データファイルを読み込む
int GameMotionParser::readGameMotionFile()
{
  const int BUF_SIZE = 128;
  char row[BUF_SIZE];

  // ファイル読み込み
  FILE* fp = fopen(GameMotionParser::sourceFileName, "r");

  // ファイル読み込み失敗
  if(fp == NULL) {
    printf("%s file not open!\n", GameMotionParser::sourceFileName);
    return -1;
  }

  // ファイル用見込み成功
  printf("%s file opened!\n", GameMotionParser::sourceFileName);
  while(fgets(row, BUF_SIZE, fp) != NULL) {
    printf("%s", row);
  }

  // ファイルを閉じる
  fclose(fp);

  return 0;
}