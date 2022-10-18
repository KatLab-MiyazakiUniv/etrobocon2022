/**
 * @file   EtRobocon2022.cpp
 * @brief  全体を制御するクラス
 * @author Takahiro55555 mutotaka0426 kawanoichi kodama0720
 */

#include "EtRobocon2022.h"
#include "LineTraceArea.h"
#include "GameArea.h"
#include "Calibrator.h"

void EtRobocon2022::start()
{
  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域
  Logger logger;

  bool isLeftCourse = true;
  bool isLeftEdge = true;
  int targetBrightness = (WHITE_BRIGHTNESS + BLACK_BRIGHTNESS) / 2;
  Calibrator calibrator;

  // 強制終了(CTRL+C)のシグナルを登録する
  signal(SIGINT, sigint);

  // サーバを起動する
  system("bash ./etrobocon2022/scripts/serve.sh &");

  // キャリブレーションする
  calibrator.run();
  isLeftCourse = calibrator.getIsLeftCourse();
  isLeftEdge = isLeftCourse;
  targetBrightness = calibrator.getTargetBrightness();

  // 合図を送るまで待機する
  calibrator.waitForStart();

  // カメラシステムに開始合図を送る
  system("bash ./etrobocon2022/scripts/start.sh");

  // スタートのメッセージログを出す
  const char* course = isLeftCourse ? "Left" : "Right";
  snprintf(buf, BUF_SIZE, "\nRun on the %s Course\n", course);
  logger.logHighlight(buf);

  // ライントレースエリアを走行する
  LineTraceArea::runLineTraceArea(isLeftCourse, isLeftEdge, targetBrightness);

  // ゲームエリアを攻略する
  GameArea::runGameArea(isLeftCourse, isLeftEdge, targetBrightness);

  // 走行終了のメッセージログを出す
  logger.logHighlight("The run has been completed\n");

  // ログファイルを生成する
  logger.outputToFile();
}

void EtRobocon2022::sigint(int _)
{
  Logger logger;
  logger.log("Forced termination.");  // 強制終了のログを出力
  logger.outputToFile();              // ログファイルを生成
  _exit(0);                           //システムコールで強制終了
}
