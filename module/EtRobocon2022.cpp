/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555
 */

#include "EtRobocon2022.h"
#include "Controller.h"

void EtRobocon2022::start()
{
  Rotation rotation;
  Controller controller;
  rotation.rotateLeft(90, 50);
  controller.sleep(100);
  rotation.rotateRight(90, 50);
  controller.sleep(100);
  rotation.turnForwardRightPivot(90, 50);
  controller.sleep(100);
  rotation.turnBackRightPivot(90, 50);
  controller.sleep(100);
  rotation.turnForwardLeftPivot(90, 50);
  controller.sleep(100);
  rotation.turnBackLeftPivot(90, 50);
}
