/**
 * @file TouchSensor.cpp
 * @brief タッチセンサクラスで用いる関数（ダミー）
 * @author KakinokiKanta
 */
#include "TouchSensor.h"
using namespace ev3api;

//コンストラクタ
TouchSensor::TouchSensor(ePortS port)
{
}

//タッチセンサの状態取得
bool TouchSensor::isPressed()
{
    return false;
}