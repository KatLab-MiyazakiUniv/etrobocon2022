/**
 * @file   Sleeping.h
 * @brief  自タスクスリープ
 * @author mutotaka0426
 */

#ifndef SLEEPING_H
#define SLEEPING_H

#include "Motion.h"

class Sleeping : public Motion {
 public:
  /**
   * コンストラクタ
   * @param milliSec スリープ時間(ミリ秒)
   */
  Sleeping(int milliSec);

  /**
   * @brief 自タスクスリープする
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  int milliSec;
};

#endif
