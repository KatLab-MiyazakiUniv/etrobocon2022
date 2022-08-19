/**
 * @file   EtRobocon2022.cpp
 * @brief  全体を制御するクラス
 * @author Takahiro55555 mutotaka0426 kawanoichi kodama0720
 */


#include <sys/time.h>
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
  //int targetBrightness = (WHITE_BRIGHTNESS + BLACK_BRIGHTNESS) / 2;
  int targetBrightness = 48;
  Calibrator calibrator;

  unsigned int sec;
    int nsec;
    double d_sec;
    
    struct timespec start_time, end_time;

    

  // キャリブレーションする
  calibrator.run();
  isLeftCourse = calibrator.getIsLeftCourse();
  isLeftEdge = isLeftCourse;
  targetBrightness = calibrator.getTargetBrightness();

  // 合図を送るまで待機する
  calibrator.waitForStart();

  /* 処理開始前の時間を取得 */
    clock_gettime(CLOCK_REALTIME, &start_time);

    /* 時間を計測する処理 */


  // スタートのメッセージログを出す
  const char* course = isLeftCourse ? "Left" : "Right";
  snprintf(buf, BUF_SIZE, "\nRun on the %s Course\n", course);
  logger.logHighlight(buf);



  // ライントレースエリアを走行する
  LineTraceArea::runLineTraceArea(isLeftCourse, isLeftEdge, targetBrightness);

    /* 処理開始後の時間とクロックを取得 */
    clock_gettime(CLOCK_REALTIME, &end_time);

    /* 処理中の経過時間を計算 */
    sec = end_time.tv_sec - start_time.tv_sec;
    nsec = end_time.tv_nsec - start_time.tv_nsec;

    d_sec = (double)sec
        + (double)nsec / (1000 * 1000 * 1000);

    /* 計測時間の表示 */
    printf(
        "time:%f\n", d_sec
    );

  // ゲームエリアを攻略する
  GameArea::runGameArea(isLeftCourse, isLeftEdge, targetBrightness);
}
