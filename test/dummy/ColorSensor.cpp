/**
 * @file ColorSensor.cpp
 * @brief カラーセンサクラスで用いる関数（ダミー）
 * @author KakinokiKanta
 */

#include "ColorSensor.h"
#include <stdio.h>
using namespace ev3api;

//コンストラクタ
ColorSensor::ColorSensor(ePortS port) {}

// RGB値を取得
void ColorSensor::getRawColor(rgb_raw_t& rgb)
{
  int index = rand() % 6;
  switch(index) {
    case 0:
      rgb = { 8, 9, 10 };  // black
      break;
    case 1:
      rgb = { 104, 101, 146 };  // white
      break;
    case 2:
      rgb = { 111, 19, 19 };  // red
      break;
    case 3:
      rgb = { 120, 108, 71 };  // yellow
      break;
    case 4:
      rgb = { 4, 75, 35 };  // green
      break;
    case 5:
      rgb = { 81, 92, 144 };  // blue
      break;
  }
}
