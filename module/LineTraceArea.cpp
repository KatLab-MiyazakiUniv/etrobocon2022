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
  const int BUF_SIZE = 128;
  int size = 0;        // 区間の数
  char buf[BUF_SIZE];  // log用にメッセージを一時保存する
  Logger logger;

  // ファイルから受け取るパラメータ.
  vector<SectionParam> sectionParams;

  // LとRどちらのパラメータを読み込むかを設定
  char* sourceFileName = isLeftCourse ? leftSourceFileName : rightSourceFileName;
  FILE* fp = fopen(sourceFileName, "r");

  // ファイル読み込み失敗
  if(fp == NULL) {
    sprintf(buf, "%s file not open!\n", sourceFileName);
    logger.logWarning(buf);
    return;
  }

  // 各行の文字を一時的に保持する領域
  char row[BUF_SIZE];
  // 区切り文字
  const char separator = ',';

  // 行ごとにパラメータを読み込む
  while(fgets(row, BUF_SIZE, fp) != NULL) {
    vector<char*> params;
    // 区切り文字を'\0'に置換したrowをparamに代入する
    char* param = strtok(row, &separator);
    while(param != NULL) {
      // paramをパラメータとして保持する
      params.push_back(param);
      // 次のパラメータをparamに代入する
      // strtok()は第1引数にNULLを与えると、前回の続きのアドレスから処理が開始される
      param = strtok(NULL, &separator);
    }
    // 取得したパラメータの型を直す
    SectionParam sectionParam = { atof(params[0]),
                                  atoi(params[1]),
                                  { atof(params[2]), atof(params[3]), atof(params[4]) } };
    sectionParams.push_back(sectionParam);
  }

  // ファイルを閉じる
  fclose(fp);

  // LineTracerにエッジを与えてインスタンス化する
  LineTracer lineTracer(isLeftEdge);

  // ログメッセージ
  const char* course = isLeftCourse ? "Left" : "Right";
  sprintf(buf, "\nRun on the %s Course\n", course);
  logger.logHighlight(buf);

  // 各区間のパラメータでライントレースする
  for(auto itr = sectionParams.begin(); itr != sectionParams.end(); itr++) {
    // Linetracer::runに区間の情報を渡して走行させる
    lineTracer.run(itr->distance, targetBrightness, itr->pwm, itr->pidGain);
  }
}
