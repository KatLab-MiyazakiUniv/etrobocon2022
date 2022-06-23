/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555
 */

#include "EtRobocon2022.h"
void EtRobocon2022::start()
{
  StraightRunner straight;
  straight.runStraightToDistance(1000, 30);
}
