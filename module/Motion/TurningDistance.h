/**
 * @file   TurningDistance.h
 * @brief  指定距離旋回動作
 * @author mutotaka0426
 */

#ifndef TURNING_DISTANCE_H
#define TURNING_DISTANCE_H

#include "Motion.h"
#include "Mileage.h"

class TurningDistance : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 目標距離 0~∞
   * @param _leftPwm 左モータのPWM値 -100~100
   * @param _rightPwm 右モータのPWM値 -100~100
   */
  TurningDistance(double _targetDistance, int _leftPwm, int _rightPwm);

  /**
   * @brief 指定距離だけ旋回する
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  double targetDistance;  // 目標距離 0~∞
  int leftPwm;            // 左モータのPWM値 -100~100
  int rightPwm;           // 右モータのPWM値 -100~100
};

#endif
