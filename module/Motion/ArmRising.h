/**
 * @file ArmRising.h
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
   * @param _angle アームを下げる角度 0~60
   * @param _pwm PWM値 0~40
   */
  ArmRising(int _angle, int _pwm);

  /**
   * @brief アームを上げる
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  int angle;  // 回転角度(deg) 0~60
  int pwm;    // PWM値 0~40
};

#endif
