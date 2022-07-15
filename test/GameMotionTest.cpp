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
    GameMotionChild gameMotionChild;
    double expected = 1.23;
    double actual = gameMotionChild.getMotionTime();
    EXPECT_EQ(expected, actual);
  }

  TEST(GameMotionTest, FailureRisk)
  {
    GameMotionChild gameMotionChild;
    double expected = 1.09;
    double actual = gameMotionChild.getFailureRisk();
    EXPECT_EQ(expected, actual);
  }

  // 子クラスのrunを呼び出すだけのテスト
  TEST(GameMotionTest, callRun)
  {
    GameMotionChild gameMotionChild;
    gameMotionChild.run();
  }

}  // namespace etrobocon2022_test
