/**
 * @file ColorJudgeTest.cpp
 * @brief ColorJudgeクラスをテストする
 * @author mutotaka0426 miyashita64
 */

#include "ColorJudge.h"
#include "RgbData.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {
  TEST(ColorJudgeTest, getColorZeroRgb)
  {
    rgb_raw_t rgb = { 0, 0, 0 };
    COLOR actual = ColorJudge::getColor(rgb);
    COLOR expected = COLOR::BLACK;

    EXPECT_EQ(expected, actual);
  }

  TEST(ColorJudgeTest, getColorFullRgb)
  {
    rgb_raw_t rgb = { 255, 255, 255 };
    COLOR actual = ColorJudge::getColor(rgb);
    COLOR expected = COLOR::WHITE;

    EXPECT_EQ(expected, actual);
  }

  TEST(ColorJudgeTest, getColorBlue)
  {
    COLOR expected = COLOR::BLUE;

    int size = sizeof(BLUE_DATA) / sizeof(BLUE_DATA[0]);
    for(int i = 0; i < size; i++) {
      COLOR actual = ColorJudge::getColor(BLUE_DATA[i]);
      EXPECT_EQ(expected, actual);
    }
  }

  TEST(ColorJudgeTest, getColorGreen)
  {
    COLOR expected = COLOR::GREEN;

    int size = sizeof(GREEN_DATA) / sizeof(GREEN_DATA[0]);
    for(int i = 0; i < size; i++) {
      COLOR actual = ColorJudge::getColor(GREEN_DATA[i]);
      EXPECT_EQ(expected, actual);
    }
  }

  TEST(ColorJudgeTest, getColorYellow)
  {
    COLOR expected = COLOR::YELLOW;

    int size = sizeof(YELLOW_DATA) / sizeof(YELLOW_DATA[0]);
    for(int i = 0; i < size; i++) {
      COLOR actual = ColorJudge::getColor(YELLOW_DATA[i]);
      EXPECT_EQ(expected, actual);
    }
  }

  TEST(ColorJudgeTest, getColorRed)
  {
    COLOR expected = COLOR::RED;

    int size = sizeof(RED_DATA) / sizeof(RED_DATA[0]);
    for(int i = 0; i < size; i++) {
      COLOR actual = ColorJudge::getColor(RED_DATA[i]);
      EXPECT_EQ(expected, actual);
    }
  }

}  // namespace etrobocon2022_test
