/**
 * @file SonarSensor.h
 * @brief ソナーセンサクラスで用いる関数（ダミー）
 * @author mutotaka0426
 */

#ifndef SONAR_SENSOR_H
#define SONAR_SENSOR_H

#include "Port.h"

namespace ev3api {

  //ソナーセンサクラス
  class SonarSensor {
   public:
    /**
     * コンストラクタ
     * @param port ソナーセンサポート番号
     * @return -
     */
    explicit SonarSensor(ePortS port);

    /**
     * 距離を測定する
     */
    int getDistance();

   private:
    int distance;
  };
}  // namespace ev3api

#endif
