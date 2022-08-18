/**
 * @file   Sleeping.cpp
 * @brief  自タスクスリープ
 * @author mutotaka0426
 */

#include "Sleeping.h"

Sleeping::Sleeping(int _milliSec) : milliSec(_milliSec) {}

void Sleeping::run()
{
  controller.sleep(milliSec);
}

void Sleeping::logRunning()
{
  logger.log("Run Sleeping");
}
