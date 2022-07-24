/**
 * @file GameMotionChild.cpp
 * @brief GameMotionの子クラス(ダミー)
 * @author kodama0720
 */

#include "GameMotionChild.h"

GameMotionChild::GameMotionChild() : GameMotion(1.23, 1.09) {}

void GameMotionChild::run()
{
  straightRunner.run(120, 50);
}
