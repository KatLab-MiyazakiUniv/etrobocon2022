/**
 * @file TouchSensor.h
 * @brief タッチセンサクラス（ダミー）
 * @author KakinokiKanta
 */
#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include "Port.h"

namespace ev3api
{

    //タッチセンサクラス
    class TouchSensor
    {
    public:
        /**
         * コンストラクタ
         * @param port タッチセンサ接続ポート
         * @return -
         */
        explicit TouchSensor(ePortS port);

        /**
         * タッチセンサ状態取得
         * @return true:押されている状態, false:押されていない状態
         */
        bool isPressed();
    };
} // namespace ev3api

#endif