/**
 * @file Measurer.cpp
 * @brief 計測に用いる関数をまとめたラッパークラス
 * @author KakinokiKanta
 */

#include "Measurer.h"

Measurer::Measurer() : colorSensor(PORT_2), leftWheel(PORT_C), rightWheel(PORT_B), armMotor(PORT_A)
{
}

// 明るさを取得
// 参考: https://tomari.org/main/java/color/ccal.html
int Measurer::getBrightness()
{
  // RGBモードと光センサモードを併用すると動作が悪くなるためRGBモードで取得する
  // 参考: https://qiita.com/kawanon868/items/5d52eb291c3f71af0419
  rgb_raw_t rgb = getRawColor();
  int brightness = std::max({ rgb.r, rgb.g, rgb.b }) * 100 / 255;  // 明度を取得して0-100に正規化
  return brightness;
}

// RGB値を取得
rgb_raw_t Measurer::getRawColor()
{
  rgb_raw_t rgb;
  colorSensor.getRawColor(rgb);
  return rgb;
}

//左モータ角位置取得
int Measurer::getLeftCount()
{
  return leftWheel.getCount();
}

//右モータ角位置取得
int Measurer::getRightCount()
{
  return rightWheel.getCount();
}

//アームモータ角位置取得
int Measurer::getArmMotorCount()
{
  return armMotor.getCount();
}
