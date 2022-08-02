/**
 * @file LineTraceArea.cpp
 * @brief ライントレースエリアを攻略するクラス
 * @author mutotaka0426 kawanoichi miyashita64
 */

#include "LineTraceArea.h"
using namespace std;

void LineTraceArea::runLineTraceArea(const bool isLeftCourse, bool& isLeftEdge,
                                     const int targetBrightness)
{
  int size = 0;          // 区間の数
  SectionParam* PARAMS;  // ファイルから受け取るパラメータ
  char buf[50];          // log用にメッセージを一時保存する
  Logger logger;

  // LとRどちらのパラメータを読み込むかを設定
  char* sourceFileName = isLeftCourse ? leftSourceFileName : rightSourceFileName;
  FILE* fp = fopen(sourceFileName, "r");

  // ファイル読み込み失敗
  if(fp == NULL) {
    sprintf(buf, "%s file not open!\n", sourceFileName);
    logger.logWarning(buf);
    return;
  }

  // 各行をパラメータとして読み込む
  char _comment[32];
  while(fscanf(fp, "%s,%d,%d,%f,%f,%f\n", _comment, &PARAMS[size].distance, &PARAMS[size].pwm,
               PARAMS[size].pidGain)
        != EOF) {
    size++;
  }

  // ファイルを閉じる
  fclose(fp);

  // LineTracerにエッジを与えてインスタンス化する
  LineTracer lineTracer(isLeftEdge);

  const char* course = isLeftCourse ? "Left" : "Right";
  sprintf(buf, "\nRun on the %s Course\n", course);
  logger.logHighlight(buf);
  for(int i = 0; i < size; i++) {
    // Linetracer::runに区間の情報を渡して走行させる
    lineTracer.run(PARAMS[i].distance, targetBrightness, PARAMS[i].pwm, PARAMS[i].pidGain);
  }
}
