/**
 * @file GameMotionChild.h
 * @brief GameMotionの子クラス
 * @author kodama0720
 */

#ifndef GAME_MOTION_CHILD_H
#define GAME_MOTION_CHILD_H

#include "GameMotion.h"

class GameMotionChild : public GameMotion {
 public:
  GameMotionChild();

  /**
   * @brief 何もしない関数
   */
  void run(void){};
};

#endif