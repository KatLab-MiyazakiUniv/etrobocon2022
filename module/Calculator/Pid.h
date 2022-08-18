/**
 * @file Pid.h
 * @brief PIDを計算するクラス
 * @author kawano
 */

#ifndef PID_H
#define PID_H

// PIDゲインを保持する構造体
struct PidGain {
 public:
  double kp;  // Pゲイン
  double ki;  // Iゲイン
  double kd;  // Dゲイン

  /** コンストラクタ
   * @param _kp Pゲイン
   * @param _ki Iゲイン
   * @param _kd Dゲイン
   */
  PidGain(double _kp, double _ki, double _kd);
};

class Pid {
 public:
  /** コンストラクタ
   * @param _kp Pゲイン
   * @param _ki Iゲイン
   * @param _kd Dゲイン
   * @param _targetValue 目標値
   */
  Pid(double _kp, double _ki, double _kd, double _targetValue);

  /**
   * @fn void setPidGain(double _kp, double _ki, double _kd);
   * @brief PIDゲインを設定する
   * @param _kp Pゲイン
   * @param _ki Iゲイン
   * @param _kd Dゲイン
   */
  void setPidGain(double _kp, double _ki, double _kd);

  /**
   * @fn double calculatePid(double currentValue, double delta = 0.01);
   * @brief PIDを計算する
   * @param currentValue 現在値
   * @param delta 周期[ms](デフォルト値0.01[10ms]、省略可)
   * @return PIDの計算結果(操作量)
   */
  double calculatePid(double currentValue, double delta = 0.01);

 private:
  PidGain gain;
  double preDeviation;  //前回の偏差
  double integral;      //偏差の累積
  double targetValue;   //目標値
};

#endif
