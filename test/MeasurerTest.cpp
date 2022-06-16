/**
 * @file MeasurerTest.cpp
 * @brief Measurerクラスをテストする
 * @author KakinokiKanta
 */

#include "Measurer.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {
  TEST(getRawColorTest, getRawColorRed)
  {
    Measurer measurer;
    int expected1 = 8;
    int expected2 = 111;
    int actual = measurer.getRawColor().r;

    ASSERT_TRUE(actual == expected1 || actual == expected2);
  }
}  // namespace etrobocon2022_test