/**
 * @file   NoneMotion.h
 * @brief  未定義動作
 * @author mutotaka0426
 */

#ifndef NONE_MOTION_H
#define NONE_MOTION_H

#include "Motion.h"

class NoneMotion : public Motion {
 public:
  /**
   * コンストラクタ
   */
  NoneMotion();

  /**
   * @brief 実行する（未定義）
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();
};

#endif
