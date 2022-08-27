/**
 * @file ArmKeeper.cpp
 * @brief アームを水平に保つクラス
 * @author miyashita64
 */

#include "ArmKeeper.h"

bool ArmKeeper::armFlag = true;

void ArmKeeper::start()
{
  // 角度を変えるために最低限必要なPWM値
  static constexpr int MIN_PWM = 30;

  Measurer measurer;
  Controller controller;

  // 0はRasPike起動時のアームの角度(モータの回転量)
  int maxCount = 0;
  int currentCount = measurer.getArmMotorCount();
  // currentCountより小さい値で初期化
  int prevCount = currentCount - 1;
  int pwm = 0;
  while(true) {
    if(armFlag){
      // 現在のアームの角度を取得する
      currentCount = measurer.getArmMotorCount();

      // 回転量の最大値(最もアームが低い)を保持する
      if(maxCount < currentCount) {
        maxCount = currentCount;
      }

      // アームが下がる(回転量が大きくなる)余地があれば調整する
      pwm = (currentCount > prevCount || maxCount > currentCount) ? MIN_PWM : 0;
      controller.setArmMotorPwm(pwm);

      prevCount = currentCount;
    }
    controller.sleep();
  }
}

// フラグのセット
void ArmKeeper::setArmFlag(bool _armFlag)
{
  armFlag = _armFlag;
};