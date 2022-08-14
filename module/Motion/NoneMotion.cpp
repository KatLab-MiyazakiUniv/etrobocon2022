/**
 * @file   NoneMotion.cpp
 * @brief  未定義動作
 * @author mutotaka0426
 */

#include "NoneMotion.h"

NoneMotion::NoneMotion() {}

void NoneMotion::run()
{
  logger.log("NoneMotion::run()");
}

void NoneMotion::logRunning()
{
  logger.logWarning("Run NoneMotion");
}
