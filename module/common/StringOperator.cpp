/**
 * @file StringOperator.cpp
 * @brief 文字列を操作するstatic関数をを持つクラス
 * @author mutotaka0426
 */

#include "StringOperator.h"

char* StringOperator::removeEOL(const char* _str)
{
  Logger logger;

  char* str;               // 戻り値となる変数
  int endIndex;            // strの末尾のインデックス
  int len = strlen(_str);  // 文字列長

  str = (char*)malloc(sizeof(char) * len);
  strcpy(str, _str);

  if(len > 0) {
    endIndex = len - 1;
  } else {
    logger.logWarning("The parameter passed to StringOperator::removeEOL is empty");
    return str;
  }

  // 末尾の改行コードを削除（LF,CR,CR+LF対応）
  if(str[endIndex] == 0x0a) {  // LFの場合
    str[endIndex] = 0x00;      // NULL文字に置き換える
    endIndex--;                // CR+LFの時のためにインデックスを一つ戻す
  }
  if(str[endIndex] == 0x0d) {  // CRの場合
    str[endIndex] = 0x00;      // NULL文字に置き換える
  }

  return str;
}
