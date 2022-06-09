/**
 * @file ColorSensor.h
 * @brief カラーセンサクラス（ダミー）
 * @author KakinokiKanta
 */

#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include "Port.h"
#include <stdlib.h>

typedef struct
{
    int r, g, b;
} rgb_raw_t;

namespace ev3api
{

    //カラーセンサクラス
    class ColorSensor
    {
    public:
        int brightness = 0;

        /**
         * コンストラクタ
         * @param port カラーセンサポート番号
         * @return -
         */
        explicit ColorSensor(ePortS port);

        /**
         * 明るさを取得
         * @return 反射光の強さ(0-100)
         */
        int getBrightness(); //明るさを取得

        /**
         * RGB値を取得
         * @return RGBを保持するクラス
         */
        void getRawColor(rgb_raw_t &rgb);
    };
} // namespace ev3api

#endif