/**
 * @file StringOperator.cpp
 * @brief 文字列を操作するstatic関数をを持つクラス
 * @author mutotaka0426
 */

#include "StringOperator.h"

void StringOperator::removeEOL(char* string)
{
  Logger logger;

  int endIndex;              // stringの末尾のインデックス
  int len = strlen(string);  // 文字列長
  if(len > 0) {
    endIndex = len - 1;
  } else {
    logger.logWarning("The parameter passed to StringOperator::removeEOL is empty");
    return;
  }
  // 末尾の改行コードを削除（LF,CR,CR+LF対応）
  if(string[endIndex] == 0x0a) {  // LFの場合
    string[endIndex] = 0x00;      // NULL文字に置き換える
    endIndex--;                   // CR+LFの時のためにインデックスを一つ戻す
  }
  if(string[endIndex] == 0x0d) {  // CRの場合
    string[endIndex] = 0x00;      // NULL文字に置き換える
  }
}
