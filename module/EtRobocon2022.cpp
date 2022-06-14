/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author sakakibara
 */

#include "EtRobocon2022.h"

void EtRobocon2022::start()
{
    Controller controller;
    while (1)
    {
        controller.setArmMotorPwm(10);
        controller.setLeftMotorPwm(50);
        controller.setRightMotorPwm(50);
    }
}