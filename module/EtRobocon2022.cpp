/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555
 */

#include "EtRobocon2022.h"
#include "Controller.h"
#include "Rotation.h"
#include "stdio.h"

void EtRobocon2022::start()
{
  Rotation rotation;
  rotation.rotateLeft(90, 50);
}
