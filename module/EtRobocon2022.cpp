/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555
 */

#include "EtRobocon2022.h"
void EtRobocon2022::start()
{
    Controller controller;
    while (1)
    {
        controller.setLeftMotorPwm(100);
        controller.setRightMotorPwm(100);
        controller.setArmMotorPwm(10);
        printf("a\n");
    }
}