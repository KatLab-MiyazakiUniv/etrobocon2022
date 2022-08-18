/**
 * @file MotionChild.h
 * @brief Motionの子クラス(ダミー)
 * @author kodama0720 mutotaka0426
 */

#ifndef MOTION_CHILD_H
#define MOTION_CHILD_H

#include "Motion.h"
#include "Mileage.h"

class MotionChild : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 目標距離 0~∞
   * @param _pwm PWM値 -100~100
   */
  MotionChild(double _targetDistance, int _pwm);

  /**
   * @brief 右方向に旋回する
   */
  void run();

  /**
   * @brief インスタンス化のログを取る
   */
  void logRunning();

 private:
  double targetDistance;
  int pwm;
};

#endif
