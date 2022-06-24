/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555
 */

#include "EtRobocon2022.h"
#include "Controller.h"
#include "stdio.h"

void EtRobocon2022::start()
{
  Controller controller;
  while(1){
    controller.setRightMotorPwm(50);
    controller.setLeftMotorPwm(50);
  }
}
