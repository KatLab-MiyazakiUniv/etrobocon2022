/**
 * @file   CorrectingRotation.h
 * @brief  角度補正回頭
 * @author mutotaka0426 kawanoichi
 */

#ifndef CORRECTING_ROTATION_H
#define CORRECTING_ROTATION_H

#include "Motion.h"
#include "Mileage.h"
#include "SystemInfo.h"

class CorrectingRotation : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetAngle 目標角度(deg) 0~89
   * @param _pwm PWM値 0~100
   */
  CorrectingRotation(int _targetAngle, int _pwm);

  /**
   * @brief 角度補正回頭する
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  static constexpr int noCorrectionAngle = 3;  // 補正免除角度 TODO: 値を決定する
  int targetAngle;                             // 目標角度(deg) 0~89
  int pwm;                                     // PWM値 0~100
};

#endif
