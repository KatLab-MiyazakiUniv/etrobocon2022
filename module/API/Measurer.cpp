/**
 * @file Measurer.cpp
 * @brief 計測に用いる関数
 * @author KakinokiKanta
 */

#include "Measurer.h"

Measurer::Measurer()
    : colorSensor(PORT_3), leftWheel(PORT_C), rightWheel(PORT_B), armMotor(PORT_A), touchSensor(PORT_1)
{
}

//明るさを取得
int Measurer::getBrightness()
{
    return colorSensor.getBrightness();
}

// RGB値を返す
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

//タッチセンサの状態取得
bool Measurer::isPressed()
{
    return touchSensor.isPressed();
}

//コース情報の取得
int Measurer::getCourseInfo(ETROBOC_COURSE_INFO_ID info)
{
    return ETRoboc_getCourseInfo(info);
}