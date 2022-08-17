/**
 * @file   EdgeChanging.cpp
 * @brief  エッジ切り替え
 * @author mutotaka0426
 */

#include "EdgeChanging.h"

EdgeChanging::EdgeChanging(bool& _isLeftEdge, bool _nextEdge)
  : isLeftEdge(_isLeftEdge), nextEdge(_nextEdge)
{
}

void EdgeChanging::run()
{
  isLeftEdge = nextEdge;
}

void EdgeChanging::logRunning()
{
  const int BUF_SIZE = 256;
  char buf[BUF_SIZE];  // log用にメッセージを一時保存する領域
  const char* isLeftEdgeStr = isLeftEdge ? "true" : "false";
  const char* nextEdgeStr = nextEdge ? "true" : "false";

  snprintf(buf, BUF_SIZE, "Run EdgeChanging (isLeftEdge: %s, nextEdge: %s)", isLeftEdgeStr,
           nextEdgeStr);
  logger.log(buf);
}
