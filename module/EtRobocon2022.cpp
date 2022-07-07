/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555 mutotaka0426
 */

#include "EtRobocon2022.h"
#include "LineTraceArea.h"

void EtRobocon2022::start()
{
  bool isLeftCourse = true;             // true:Lコース, false:Rコース
  int targetBrightness = (93 - 3) / 2;  // 目標輝度
  LineTraceArea::runLineTraceArea(isLeftCourse, targetBrightness);
}
