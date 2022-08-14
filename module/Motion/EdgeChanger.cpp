/**
 * @file   EdgeChanger.cpp
 * @brief  エッジ切り替え
 * @author mutotaka0426
 */

#include "EdgeChanger.h"

EdgeChanger::EdgeChanger(bool& _isLeftEdge, bool _nextEdge)
  : isLeftEdge(_isLeftEdge), nextEdge(_nextEdge)
{
}

void EdgeChanger::run()
{
  isLeftEdge = nextEdge;
}

void EdgeChanger::logRunning()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保存する
  const char* isLeftEdgeStr = isLeftEdge ? "true" : "false";
  const char* nextEdgeStr = nextEdge ? "true" : "false";

  sprintf(buf, "Run EdgeChanger (isLeftEdge: %s, nextEdge: %s)", isLeftEdgeStr, nextEdgeStr);
  logger.log(buf);
}
