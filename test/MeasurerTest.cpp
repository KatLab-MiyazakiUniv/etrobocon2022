/**
 * @file MeasurerTest.cpp
 * @brief Measurerクラスをテストする
 * @author KakinokiKanta
 */

#include "Measurer.h"
#include <gtest/gtest.h>

// rgb_raw_tの比較用関数
bool eqRgb(rgb_raw_t rgb1, rgb_raw_t rgb2)
{
  return rgb1.r == rgb2.r && rgb1.g == rgb2.g && rgb1.b == rgb2.b;
}

namespace etrobocon2022_test {
  TEST(MeasurerTest, getRawColor)
  {
    Measurer measurer;
    rgb_raw_t expected1 = { 8, 9, 10 };       // black
    rgb_raw_t expected2 = { 104, 101, 146 };  // white
    rgb_raw_t expected3 = { 111, 19, 19 };    // red
    rgb_raw_t expected4 = { 120, 108, 71 };   // yellow
    rgb_raw_t expected5 = { 4, 75, 35 };      // green
    rgb_raw_t expected6 = { 81, 92, 144 };    // blue
    rgb_raw_t actual = measurer.getRawColor();

    ASSERT_TRUE(eqRgb(actual, expected1) || eqRgb(actual, expected2) || eqRgb(actual, expected3)
                || eqRgb(actual, expected4) || eqRgb(actual, expected5)
                || eqRgb(actual, expected6));
  }
}  // namespace etrobocon2022_test
