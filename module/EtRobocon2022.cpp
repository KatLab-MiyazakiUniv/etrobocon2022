/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555
 */

#include "EtRobocon2022.h"
#include "Controller.h"
#include "Rotation.h"
#include "StraightRunner.h"
#include "stdio.h"

void EtRobocon2022::start()
{
  Rotation rotation;
  StraightRunner straightRunner;
  Controller controller;
  Measurer measurer;
  printf("left\n");
  rotation.rotateLeft(90, 80);
  controller.sleep(1000);

  printf("right\n");
  rotation.rotateRight(90, 80);
  controller.sleep(1000);

  printf("right pivot forward\n");
  rotation.turnForwardRightPivot(90, 80);
  controller.sleep(1000);

  printf("right pivot back\n");
  rotation.turnBackRightPivot(90, 80);
  controller.sleep(1000);

  printf("left pivot forward\n");
  rotation.turnForwardLeftPivot(90, 80);
  controller.sleep(1000);

  printf("left pivot back\n");
  rotation.turnBackLeftPivot(90, 80);
  controller.sleep(1000);

  printf("Straight\n");
  straightRunner.runStraightToDistance(500, 100);

  printf("Finish\n");
}
