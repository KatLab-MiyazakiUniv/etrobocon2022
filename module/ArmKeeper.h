/**
 * @file ArmKeeper.h
 * @brief アームを水平に保つクラス
 * @author miyashita64
 */

#ifndef ARM_KEEPER_H
#define ARM_KEEPER_H

#include "Measurer.h"
#include "Controller.h"

class ArmKeeper {
 public:
  static void start();
  static void setArmFlag(bool _armFlag);

 private:
  ArmKeeper();  // インスタンス化を禁止する

  // アームを水平に維持するかのフラグ(true:調整する/false:調整しない)
  static bool armFlag;
};

#endif
