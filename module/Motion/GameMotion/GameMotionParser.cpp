/**
 * @file GameMotionParser.cpp
 * @brief ソースファイルをゲーム動作に解釈する
 * @author miyashita64, kawano
 */

#include "GameMotionParser.h"

int GameMotionParser::parseGameMotionFile()
{
  const int BUF_SIZE = 128;
  char row[BUF_SIZE];

  FILE* fp = fopen(GameMotionParser::sourceFileName, "r");

  if(fp == NULL) {
    printf("%s file not open!\n", GameMotionParser::sourceFileName);
    return -1;
  }

  printf("%s file opened!\n", GameMotionParser::sourceFileName);
  while(fgets(row, BUF_SIZE, fp) != NULL) {
    printf("%s", row);
  }

  fclose(fp);

  return 0;
}