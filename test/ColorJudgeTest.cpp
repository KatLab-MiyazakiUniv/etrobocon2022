/**
 * @file ColorJudgeTest.cpp
 * @brief ColorJudgeクラスをテストする
 * @author mutotaka0426
 */

#include "ColorJudge.h"
#include <gtest/gtest.h>

namespace etrobocon2021_test {
  TEST(getColorTest, getColorTrueBlack)
  {
    rgb_raw_t rgb = { 0, 0, 0 };
    COLOR expected = COLOR::BLACK;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightBlack)
  {
    rgb_raw_t rgb = { 39, 39, 58 };
    COLOR expected = COLOR::BLACK;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkBlack)
  {
    rgb_raw_t rgb = { 4, 5, 8 };
    COLOR expected = COLOR::BLACK;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightRed)
  {
    rgb_raw_t rgb = { 119, 81, 109 };
    COLOR expected = COLOR::RED;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkRed)
  {
    rgb_raw_t rgb = { 111, 19, 19 };
    COLOR expected = COLOR::RED;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightRed2)
  {
    rgb_raw_t rgb = { 101, 76, 107 };
    COLOR expected = COLOR::RED;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkRed2)
  {
    rgb_raw_t rgb = { 93, 16, 16 };
    COLOR expected = COLOR::RED;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightYellow)
  {
    rgb_raw_t rgb = { 120, 108, 71 };
    COLOR expected = COLOR::YELLOW;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkYellow)
  {
    rgb_raw_t rgb = { 120, 104, 8 };
    COLOR expected = COLOR::YELLOW;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightYellow2)
  {
    rgb_raw_t rgb = { 104, 96, 71 };
    COLOR expected = COLOR::YELLOW;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkYellow2)
  {
    rgb_raw_t rgb = { 104, 92, 8 };
    COLOR expected = COLOR::YELLOW;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightGreen)
  {
    rgb_raw_t rgb = { 72, 100, 106 };
    COLOR expected = COLOR::GREEN;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkGreen)
  {
    rgb_raw_t rgb = { 4, 75, 35 };
    COLOR expected = COLOR::GREEN;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightGreen2)
  {
    rgb_raw_t rgb = { 85, 94, 124 };
    COLOR expected = COLOR::GREEN;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkGreen2)
  {
    rgb_raw_t rgb = { 4, 64, 29 };
    COLOR expected = COLOR::GREEN;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightBlue)
  {
    rgb_raw_t rgb = { 81, 92, 144 };
    COLOR expected = COLOR::BLUE;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkBlue)
  {
    rgb_raw_t rgb = { 4, 45, 112 };
    COLOR expected = COLOR::BLUE;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightBlue2)
  {
    rgb_raw_t rgb = { 83, 89, 137 };
    COLOR expected = COLOR::BLUE;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkBlue2)
  {
    rgb_raw_t rgb = { 4, 40, 103 };
    COLOR expected = COLOR::BLUE;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorLightWhite)
  {
    rgb_raw_t rgb = { 104, 101, 146 };
    COLOR expected = COLOR::WHITE;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorDarkWhite)
  {
    rgb_raw_t rgb = { 92, 94, 141 };
    COLOR expected = COLOR::WHITE;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorMaxRgb)
  {
    rgb_raw_t rgb = { 112, 107, 152 };
    COLOR expected = COLOR::WHITE;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }

  TEST(getColorTest, getColorFullRgb)
  {
    rgb_raw_t rgb = { 255, 255, 255 };
    COLOR expected = COLOR::WHITE;

    EXPECT_EQ(expected, ColorJudge::getColor(rgb));
  }
}  // namespace etrobocon2021_test
