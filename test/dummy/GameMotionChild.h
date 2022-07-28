/**
 * @file GameMotionChild.h
 * @brief GameMotionの子クラス(ダミー)
 * @author kodama0720
 */

#ifndef GAME_MOTION_CHILD_H
#define GAME_MOTION_CHILD_H

#include "GameMotion.h"

class GameMotionChild : public GameMotion {
 public:
  GameMotionChild(bool& isLeftEdge);

  /**
   * @brief 前進する
   */
  void run();
};

#endif