/**
 * @file ArmFalling.h
 * @brief アームを下げるクラス
 * @author KakinokiKanta
 */

#ifndef ARM_FALLING_H
#define ARM_FALLING_H

#include "Motion.h"

class ArmFalling : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _angle アームを下げる角度 0~60
   * @param _pwm PWM値 0~40
   */
  ArmFalling(int _angle, int _pwm);

  /**
   * @brief アームを下げる
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  int angle;  // 回転角度(deg) 0~360
  int pwm;    // PWM値 0~100
};

#endif