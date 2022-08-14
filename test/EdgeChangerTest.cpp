/**
 * @file   EdgeChangerTest.cpp
 * @brief  EdgeChangerクラスのテスト
 * @author mutotaka0426
 */

#include "EdgeChanger.h"
#include <gtest/gtest.h>
#include <cmath>

namespace etrobocon2022_test {

  TEST(EdgeChanger, runFalseToFalse)
  {
    bool isLeftEdge = false;  // run()を実行することでこの変数が切り替わる
    bool nextEdge = false;
    EdgeChanger ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

  TEST(EdgeChanger, runFalseToTrue)
  {
    bool isLeftEdge = false;  // run()を実行することでこの変数が切り替わる
    bool nextEdge = true;
    EdgeChanger ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

  TEST(EdgeChanger, runTrueToFalse)
  {
    bool isLeftEdge = true;  // run()を実行することでこの変数が切り替わる
    bool nextEdge = false;
    EdgeChanger ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

  TEST(EdgeChanger, runTrueToTrue)
  {
    bool isLeftEdge = true;  // run()を実行することでこの変数が切り替わる
    bool nextEdge = true;
    EdgeChanger ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

}  // namespace etrobocon2022_test
