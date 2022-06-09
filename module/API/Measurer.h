/**
 * @file Measurer.h
 * @brief 計測に用いる関数をまとめたクラス
 * @author KakinokiKanta
 */

#ifndef MEASURER_H
#define MEASURER_H

#include "ev3api.h"
#include "ColorSensor.h"
#include "Motor.h"
#include "TouchSensor.h"
#include "etroboc_ext.h"

class Measurer
{
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

    /**
     * タッチセンサ状態取得
     * @return true:押されている状態, false:押されていない状態
     */
    bool isPressed();

    /**
     * コース情報の取得
     * @param info 取得するコース情報のID
     * @return コース情報(ブロックの座標)
     */
    int getCourseInfo(ETROBOC_COURSE_INFO_ID info);

private:
    ev3api::ColorSensor colorSensor;
    ev3api::Motor leftWheel;
    ev3api::Motor rightWheel;
    ev3api::Motor armMotor;
    ev3api::TouchSensor touchSensor;
};

#endif