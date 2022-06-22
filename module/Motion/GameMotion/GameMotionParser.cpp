/**
 * @file GameMotionParser.cpp
 * @brief ソースファイルをゲーム動作に解釈する
 * @author miyashita64, kawano
 */

#include "GameMotionParser.h"

int GameMotionParser::parseGameMotionFile()
{
  /* // ifstreamを呼び出すとmakeできない？iostreamも同様
  std::string str;
  std::ifstream ifs(GameMotionParser::sourceFileName);

  if(ifs.fail()) {
    printf("Failed to open file.");
    return -1;
  }
  while(getline(ifs, str)) {
    printf("%s\n", str.c_str());
  }

  ifs.close();
  /*/
  // C言語的にかけば、makeは通るがsim上ではfopenが失敗する(ソースコード単体で実行すれば開けた)
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
  //*/

  return 0;
}

// int main()
// {
//   GameMotionParser::parseGameMotionFile();
//   return 0;
// }