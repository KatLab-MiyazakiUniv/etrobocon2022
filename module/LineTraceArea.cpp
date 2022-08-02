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
  char buf[50];          // log用にメッセージを一時保存する
  Logger logger;

  // ファイルから受け取るパラメータ. なぜかvectorがincludeできないためやむなくmalloc.
  SectionParam* params = (SectionParam *)malloc(LIMIT_SIZE * sizeof(SectionParam));

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
  while(fscanf(fp, "%lf,%d,%lf,%lf,%lf,%s\n", &params[size].distance, &params[size].pwm,
               &params[size].pidGain.kp, &params[size].pidGain.ki, &params[size].pidGain.kd, _comment)
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
    lineTracer.run(params[i].distance, targetBrightness, params[i].pwm, params[i].pidGain);
  }
}
