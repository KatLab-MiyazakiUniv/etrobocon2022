/**
 * @file Rotation.h
 * @brief 回頭・ピボットターンするクラス
 * @author sugaken0528
 */

#ifndef ROTATION_H
#define ROTATION_H

#include <cmath>
#include <algorithm>
#include "Controller.h"
#include "Measurer.h"
#include "Mileage.h"
#include "Logger.h"

/**
 * 回頭とピボットターンをするクラス
 */
class Rotation {
 public:
  /**
   * コンストラクタ
   */
  Rotation();

  /**
   * 左に回頭する関数
   * @param angle 回転角度(deg) 0~360
   * @param pwm PWM値 0~100
   */
  void rotateLeft(int angle, int pwm);

  /**
   * 右に回頭する関数
   * @param angle 回転角度(deg) 0~360
   * @param pwm PWM値 0~100
   */
  void rotateRight(int angle, int pwm);

  /**
   * 右タイヤを軸に前方へピボットターンする関数
   * @param angle　回転角度(deg) 0~360
   * @param pwm PWM値 0~100
   */
  void turnForwardRightPivot(int angle, int pwm);

  /**
   * 右タイヤを軸に後方へピボットターンする関数
   * @param angle　回転角度(deg) 0~360
   * @param pwm PWM値 0~100
   */
  void turnBackRightPivot(int angle, int pwm);

  /**
   * 左タイヤを軸に前方へピボットターンする関数
   * @param angle　回転角度(deg) 0~360
   * @param pwm PWM値 0~100
   */
  void turnForwardLeftPivot(int angle, int pwm);

  /**
   * 左タイヤを軸に後方へピボットターンする関数
   * @param angle　回転角度(deg) 0~360
   * @param pwm PWM値 0~100
   */
  void turnBackLeftPivot(int angle, int pwm);

 private:
  Controller controller;
  Measurer measurer;

  const double RADIUS;       // 車輪の半径[mm]
  const double TREAD;        // 走行体のトレッド幅（両輪の間の距離）[mm]
  const int ROTATE_MIN_PWM;  // 回頭の時のモーターパワーの最小値
  const int PIVOT_FRONT_MIN_PWM;  //ピボットターン前方向の時のモーターパワーの最小値
  const int PIVOT_BACK_MIN_PWM;  //ピボットターン後方向の時のモーターパワーの最小値

  /**
   *  @brief 指定角度回頭したときの片輪の回転角度を計算する
   *  @param Angle [走行体が回頭する角度[deg]]
   *  @return 片輪の回転角度(回転方向に関わらず正の数)
   */
  double calculateTireAngle(int angle);
};

#endif