/**
 * @file   LineTraceArea.cpp
 * @brief  ライントレースエリアを攻略するクラス
 * @author mutotaka0426 kawanoichi sap2368 miyashita64
 */

#include "LineTraceArea.h"

using namespace std;

void LineTraceArea::runLineTraceArea(const bool isLeftCourse, bool& isLeftEdge,
                                     const int targetBrightness)
{
  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保存する
  Logger logger;

  // ファイルから受け取る動作リスト
  vector<Motion*> motionList;

  // LとRどちらのパラメータを読み込むかを設定
  const char* filePath = isLeftCourse ? lineTraceAreaLeft : lineTraceAreaRight;
  // 動作インスタンスのリストを生成する
  motionList = MotionParser::createMotions(filePath, targetBrightness, isLeftEdge);

  // 動作実行のメッセージ
  sprintf(buf, "\nRun the commands in '%s'\n", filePath);
  logger.logHighlight(buf);

  // 各動作を実行する
  for(const auto& motion : motionList) {
    motion->logRunning();
    motion->run();
  }
}
