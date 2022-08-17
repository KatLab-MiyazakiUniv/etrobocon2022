/**
 * @file   EdgeChangingTest.cpp
 * @brief  EdgeChangingクラスのテスト
 * @author mutotaka0426
 */

#include "EdgeChanging.h"
#include <gtest/gtest.h>
#include <cmath>

namespace etrobocon2022_test {

  TEST(EdgeChanging, runFalseToFalse)
  {
    bool isLeftEdge = false;  // run()を実行することでこの変数が切り替わる（ecに参照渡しするため）
    bool nextEdge = false;
    EdgeChanging ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

  TEST(EdgeChanging, runFalseToTrue)
  {
    bool isLeftEdge = false;  // run()を実行することでこの変数が切り替わる（ecに参照渡しするため）
    bool nextEdge = true;
    EdgeChanging ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

  TEST(EdgeChanging, runTrueToFalse)
  {
    bool isLeftEdge = true;  // run()を実行することでこの変数が切り替わる（ecに参照渡しするため）
    bool nextEdge = false;
    EdgeChanging ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

  TEST(EdgeChanging, runTrueToTrue)
  {
    bool isLeftEdge = true;  // run()を実行することでこの変数が切り替わる（ecに参照渡しするため）
    bool nextEdge = true;
    EdgeChanging ec(isLeftEdge, nextEdge);

    ec.run();

    bool expected = nextEdge;
    bool actual = isLeftEdge;

    EXPECT_EQ(expected, actual);
  }

}  // namespace etrobocon2022_test
