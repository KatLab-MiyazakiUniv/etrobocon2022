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
  bool _isLeftCourse = true;

  printf("Select a Course\n");
  printf(">> Set Left Course\n");

  // 中央ボタンが押されたら確定する
  while(!measurer.getEnterButton()) {
    // 左ボタンが押されたらLコースをセットする
    if(measurer.getLeftButton() && !_isLeftCourse) {
      _isLeftCourse = true;
      printf(">> Set Left Course\n");
    }

    // 右ボタンが押されたらRコースをセットする
    if(measurer.getRightButton() && _isLeftCourse) {
      _isLeftCourse = false;
      printf(">> Set Right Course\n");
    }

    controller.sleep();  // 10ミリ秒スリープ
  }

  isLeftCourse = _isLeftCourse;
  std::string course = isLeftCourse ? "Left" : "Right";

  printf("\x1b[32m");  // 文字色を緑に
  printf("\nWill Run on the %s Course\n", course.c_str());
  printf("\x1b[39m\n");       // 文字色をデフォルトに戻す
  controller.sleep(1000000);  // 1秒スリープ
}

void Calibrator::measureTargetBrightness()
{
  // 黒と白の輝度（初期化の値はロボコン部屋で取得した値）
  int blackBrightness = BLACK_BRIGHTNESS;
  int whiteBrightness = WHITE_BRIGHTNESS;

  // 黒の上で中央ボタンを押して黒の輝度を取得する
  printf("Press the Center Button on the Black\n");
  // 中央ボタンが押されるまで待機
  while(!measurer.getEnterButton()) {
    controller.sleep();  // 10ミリ秒スリープ
  }
  blackBrightness = measurer.getBrightness();
  printf(">> Black Brightness Value is %d\n", blackBrightness);
  controller.sleep(1000000);  // 1秒スリープ

  // 白の上で中央ボタンを押して白の輝度を取得する
  printf("Press the Center Button on the White\n");
  // 中央ボタンが押されるまで待機
  while(!measurer.getEnterButton()) {
    controller.sleep();  // 10ミリ秒スリープ
  }
  whiteBrightness = measurer.getBrightness();
  printf(">> White Brightness Value is %d\n", whiteBrightness);
  controller.sleep(1000000);  // 1秒スリープ

  // 黒と白の平均値を目標輝度とする
  targetBrightness = (whiteBrightness + blackBrightness) / 2;
  printf("\x1b[32m");  // 文字色を緑に
  printf("\nTarget Brightness is %d\n", targetBrightness);
  printf("\x1b[39m\n");  // 文字色をデフォルトに戻す
}

void Calibrator::waitForStart()
{
  constexpr int startDistance = 5;  // 手などでスタート合図を出す距離[cm]

  printf("On standby.\n");
  printf("Signal within %dcm from Sonar Sensor.\n", startDistance);

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
