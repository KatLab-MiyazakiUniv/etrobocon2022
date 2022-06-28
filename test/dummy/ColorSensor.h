/**
 * @file ColorSensor.h
 * @brief カラーセンサクラス（ダミー）
 * @author KakinokiKanta
 */

#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include "Port.h"
#include <stdlib.h>

typedef struct {
  int r, g, b;
} rgb_raw_t;

namespace ev3api {

  //カラーセンサクラス
  class ColorSensor {
   public:
    /**
     * コンストラクタ
     * @param port カラーセンサポート番号
     * @return -
     */
    explicit ColorSensor(ePortS port);

    /**
     * RGB値を取得
     * @return RGBを保持するクラス
     */
    void getRawColor(rgb_raw_t& rgb);
  };
}  // namespace ev3api

#endif
