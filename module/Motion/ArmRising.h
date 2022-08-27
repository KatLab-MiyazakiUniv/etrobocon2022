/**
 * @file ArmFalling.h
 * @brief アームを上げるクラス
 * @author mutotaka0426 KakinokiKanta
 */

#ifndef ARM_RISING_H
#define ARM_RISING_H

#include "Motion.h"

class ArmRising : public Motion {
 public:
  /**
   * コンストラクタ
   */
  ArmRising(int _angle, int _pwm);

  /**
   * @brief 実行する
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
