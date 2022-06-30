/**
 * @file Measurer.h
 * @brief 計測に用いる関数をまとめたラッパークラス
 * @author KakinokiKanta
 */

#ifndef MEASURER_H
#define MEASURER_H

#include <algorithm>
#include "ev3api.h"
#include "ColorSensor.h"
#include "Motor.h"

class Measurer {
 public:
  /**
   * コンストラクタ
   */
  Measurer();

  /**
   * 明るさを取得
   * @return 反射光の強さ(0-100)
   */
  int getBrightness();

  /**
   * RGB値を取得
   * @return RGB値
   */
  rgb_raw_t getRawColor();

  /**
   * 左モータ角位置取得
   * @return 左モータ角位置[deg]
   */
  int getLeftCount();

  /**
   * 右モータ角位置取得
   * @return 右モータ角位置[deg]
   */
  int getRightCount();

  /**
   * アームモータ角位置取得
   * @return アームモータ角位置[deg]
   */
  int getArmMotorCount();

 private:
  ev3api::ColorSensor colorSensor;
  ev3api::Motor leftWheel;
  ev3api::Motor rightWheel;
  ev3api::Motor armMotor;
};

#endif
