/**
 * @file StringOperator.h
 * @brief 文字列を操作するstatic関数をを持つクラス
 * @author mutotaka0426
 */
#ifndef STRING_OPERATOR_H
#define STRING_OPERATOR_H

#include "Logger.h"

class StringOperator {
 public:
  /**
   * @brief 入力された文字列の末尾の改行を削除する
   * @param string 改行を消したい文字列
   */
  static void removeEOL(char* string);

 private:
  StringOperator();  // インスタンス化を禁止する
};

#endif
