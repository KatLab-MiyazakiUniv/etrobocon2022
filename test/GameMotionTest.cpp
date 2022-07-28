/**
 * @file GameMotionTest.cpp
 * @brief GameMotionクラスのテスト
 * @author kodama0720
 */

#include "GameMotionChild.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {
  TEST(GameMotionTest, MotionTime)
  {
    bool isLeftEdge = true;
    GameMotionChild gameMotionChild(isLeftEdge);
    double expected = 1.23;
    double actual = gameMotionChild.getMotionTime();
    EXPECT_EQ(expected, actual);
  }

  TEST(GameMotionTest, FailureRisk)
  {
    bool isLeftEdge = true;
    GameMotionChild gameMotionChild(isLeftEdge);
    double expected = 1.09;
    double actual = gameMotionChild.getFailureRisk();
    EXPECT_EQ(expected, actual);
  }

  // 子クラスのrunを呼び出すだけのテスト
  TEST(GameMotionTest, callRun)
  {
    bool isLeftEdge = true;
    GameMotionChild gameMotionChild(isLeftEdge);
    gameMotionChild.run(isLeftEdge);
  }

}  // namespace etrobocon2022_test
