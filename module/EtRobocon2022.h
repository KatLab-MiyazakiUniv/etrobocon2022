/**
 * @file   EtRobocon2022.h
 * @brief  全体を制御するクラス
 * @author Takahiro55555
 */

#ifndef ETROBOCON2022_H
#define ETROBOCON2022_H

// ev3api.hを読み込むヘッダは.cppに記述する
#include "SystemInfo.h"
#include "Logger.h"

class EtRobocon2022 {
 public:
  static void start();
};

#endif
