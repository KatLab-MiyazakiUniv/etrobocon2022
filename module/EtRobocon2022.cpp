/**
 * @file EtRobocon2022.cpp
 * @brief 全体を制御するクラス
 * @author Takahiro55555
 */

#include "EtRobocon2022.h"
#include "GameMotionParser.h"

void EtRobocon2022::start()
{
  GameMotionParser::parseGameMotionFile();
}
