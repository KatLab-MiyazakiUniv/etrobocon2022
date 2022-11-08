/**
 * @file   EtRobocon2022.cpp
 * @brief  全体を制御するクラス
 * @author Takahiro55555 mutotaka0426 kawanoichi kodama0720
 */

#include "EtRobocon2022.h"
#include "LineTraceArea.h"
#include "GameArea.h"
#include "Calibrator.h"
#include "SystemInfo.h"

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

  // 合図を送るまで待機する
  calibrator.waitForStart();

  for(int i = 0; i < 8; i++) {
    // 回頭する
    Rotation rt(45, 70, true);
    rt.run();

    // 回頭補正を行う
    if(i % 2 == 0) {
      CorrectingRotation cr(0, 65);
      cr.run();
    } else {
      CorrectingRotation cr(45, 65);
      cr.run();
    }
  }

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

  _exit(0);  //システムコールで強制終了
}
