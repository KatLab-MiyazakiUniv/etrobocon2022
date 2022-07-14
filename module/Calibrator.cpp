/**
 * @file Calibrator.cpp
 * @brief キャリブレーションからスタートまでを担当するクラス
 * @author mutotaka0426
 */

#include "Calibrator.h"

Calibrator::Calibrator()
  : isLeftCourse(true), targetBrightness((WHITE_BRIGHTNESS + BLACK_BRIGHTNESS) / 2)
{
}

void Calibrator::run()
{
  // ev3apiの出力と入り混じるので10ミリ秒スリープを入れる
  controller.sleep();

  // 左右ボタンでコースのLRを選択する
  selectCourse();

  // 黒と白の輝度を測定して目標輝度を求める
  measureTargetBrightness();
}

void Calibrator::selectCourse()
{
  char buf[50];  // log用にメッセージを一時保存する
  bool _isLeftCourse = true;

  logger.log("Select a Course");
  logger.log(">> Set Left Course");

  // 中央ボタンが押されたら確定する
  while(!measurer.getEnterButton()) {
    // 左ボタンが押されたらLコースをセットする
    if(measurer.getLeftButton() && !_isLeftCourse) {
      _isLeftCourse = true;
      logger.log(">> Set Left Course");
    }

    // 右ボタンが押されたらRコースをセットする
    if(measurer.getRightButton() && _isLeftCourse) {
      _isLeftCourse = false;
      logger.log(">> Set Right Course");
    }

    controller.sleep();  // 10ミリ秒スリープ
  }

  isLeftCourse = _isLeftCourse;
  const char* course = isLeftCourse ? "Left" : "Right";
  sprintf(buf, "\nWill Run on the %s Course", course);
  logger.logHighlight(buf);

  controller.sleep(1000000);  // 1秒スリープ
}

void Calibrator::measureTargetBrightness()
{
  char buf[50];  // log用にメッセージを一時保存する
  // 黒と白の輝度（初期化の値はロボコン部屋で取得した値）
  int blackBrightness = BLACK_BRIGHTNESS;
  int whiteBrightness = WHITE_BRIGHTNESS;

  // 黒の上で中央ボタンを押して黒の輝度を取得する
  logger.log("Press the Center Button on the Black");
  // 中央ボタンが押されるまで待機
  while(!measurer.getEnterButton()) {
    controller.sleep();  // 10ミリ秒スリープ
  }
  blackBrightness = measurer.getBrightness();
  sprintf(buf, ">> Black Brightness Value is %d", blackBrightness);
  logger.log(buf);
  controller.sleep(1000000);  // 1秒スリープ

  // 白の上で中央ボタンを押して白の輝度を取得する
  logger.log("Press the Center Button on the White");
  // 中央ボタンが押されるまで待機
  while(!measurer.getEnterButton()) {
    controller.sleep();  // 10ミリ秒スリープ
  }
  whiteBrightness = measurer.getBrightness();
  sprintf(buf, ">> White Brightness Value is %d", whiteBrightness);
  logger.log(buf);
  controller.sleep(1000000);  // 1秒スリープ

  // 黒と白の平均値を目標輝度とする
  targetBrightness = (whiteBrightness + blackBrightness) / 2;
  sprintf(buf, "\nTarget Brightness is %d", targetBrightness);
  logger.log(buf);
}

void Calibrator::waitForStart()
{
  char buf[50];                     // log用にメッセージを一時保存する
  constexpr int startDistance = 5;  // 手などでスタート合図を出す距離[cm]

  logger.log("On standby.\n");
  sprintf(buf, "Signal within %dcm from Sonar Sensor.", startDistance);
  logger.log(buf);

  // startDistance以内の距離に物体がない間待機する
  while(measurer.getForwardDistance() > startDistance) {
    controller.sleep();  // 10ミリ秒スリープ
  }
}

bool Calibrator::getIsLeftCourse()
{
  return isLeftCourse;
}

int Calibrator::getTargetBrightness()
{
  return targetBrightness;
}
