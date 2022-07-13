/**
 * @file Calibrator.h
 * @brief キャリブレーションからスタートまでを担当するクラス
 * @author mutotaka0426
 */

#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <string>
#include "Measurer.h"
#include "Controller.h"
#include "Logger.h"
#include "SystemInfo.h"

class Calibrator {
 public:
  /**
   * コンストラクタ
   */
  Calibrator();

  /**
   * キャリブレーション処理（入力系）をまとめて実行する
   */
  void run();

  /**
   * スタート合図が出るまで待機状態にする
   */
  void waitForStart();

  /**
   * isLeftCourseのゲッター
   * @return true:Lコース, false:Rコース
   */
  bool getIsLeftCourse();

  /**
   * targetBrightnessのゲッター
   * @return 目標輝度
   */
  int getTargetBrightness();

 private:
  bool isLeftCourse;     // true:左コース, false: コース
  int targetBrightness;  // 目標輝度
  Measurer measurer;
  Controller controller;
  Logger logger;

  /**
   * 左右ボタンでLRコースを選択してisLeftCourseをセットする
   */
  void selectCourse();

  /**
   * 黒と白の輝度を測定して目標輝度を求めtargetBrightnessをセットする
   */
  void measureTargetBrightness();
};

#endif
