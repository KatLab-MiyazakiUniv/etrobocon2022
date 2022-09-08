/**
 * @file   Motion.h
 * @brief  動作の親クラス
 * @author kodama0720 mutotaka0426 sugaken0528
 */

#ifndef MOTION_H
#define MOTION_H

#include "Controller.h"
#include "Measurer.h"
#include "Logger.h"

class Motion {
 public:
  /**
   * コンストラクタ
   */
  Motion();

  /**
   * @brief 動作を実行する抽象メソッド
   */
  virtual void run() = 0;

  /**
   * @brief 実行のログを取る抽象メソッド
   */
  virtual void logRunning() = 0;

 protected:
  Controller controller;
  Measurer measurer;
  Logger logger;
};

#endif
