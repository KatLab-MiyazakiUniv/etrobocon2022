/**
 * @file GameMotionChild.cpp
 * @brief GameMotionの子クラス(ダミー)
 * @author kodama0720
 */

#include "GameMotionChild.h"

GameMotionChild::GameMotionChild() : GameMotion(edge, 1.23, 1.09) {}

void GameMotionChild::run(bool& isLeftEdge)
{
  straightRunner.run(120, 50);
}
