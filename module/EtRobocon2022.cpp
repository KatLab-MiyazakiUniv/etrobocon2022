/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555 mutotaka0426
 */

#include "EtRobocon2022.h"

void EtRobocon2022::start()
{
  bool isLeftCourse = true;  // true:Lコース, false:Rコース
  LineTraceArea::runLineTraceArea(isLeftCourse);
}
