/**
 * @file   ColorJudgeTest.cpp
 * @brief  ColorJudgeクラスをテストする
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

  TEST(ColorJudgeTest, stringToColorBlack)
  {
    const char* str = "BLACK";
    COLOR expected = COLOR::BLACK;

    COLOR actual = ColorJudge::stringToColor(str);

    EXPECT_EQ(expected, actual);
  }

  TEST(ColorJudgeTest, stringToColorWhite)
  {
    const char* str = "WHITE";
    COLOR expected = COLOR::WHITE;

    COLOR actual = ColorJudge::stringToColor(str);

    EXPECT_EQ(expected, actual);
  }

  TEST(ColorJudgeTest, stringToColorBlue)
  {
    const char* str = "BLUE";
    COLOR expected = COLOR::BLUE;

    COLOR actual = ColorJudge::stringToColor(str);

    EXPECT_EQ(expected, actual);
  }

  TEST(ColorJudgeTest, stringToColorGreen)
  {
    const char* str = "GREEN";
    COLOR expected = COLOR::GREEN;

    COLOR actual = ColorJudge::stringToColor(str);

    EXPECT_EQ(expected, actual);
  }

  TEST(ColorJudgeTest, stringToColorYellow)
  {
    const char* str = "YELLOW";
    COLOR expected = COLOR::YELLOW;

    COLOR actual = ColorJudge::stringToColor(str);

    EXPECT_EQ(expected, actual);
  }

  TEST(ColorJudgeTest, stringToColorRed)
  {
    const char* str = "RED";
    COLOR expected = COLOR::RED;

    COLOR actual = ColorJudge::stringToColor(str);

    EXPECT_EQ(expected, actual);
  }

  TEST(ColorJudgeTest, stringToColorNone)
  {
    const char* str = "NONE";
    COLOR expected = COLOR::NONE;

    COLOR actual = ColorJudge::stringToColor(str);

    EXPECT_EQ(expected, actual);
  }

  TEST(ColorJudgeTest, colorToStringBlack)
  {
    COLOR color = COLOR::BLACK;
    const char* expected = "BLACK";

    const char* actual = ColorJudge::colorToString(color);

    EXPECT_STREQ(expected, actual);
  }

  TEST(ColorJudgeTest, colorToStringWhite)
  {
    COLOR color = COLOR::WHITE;
    const char* expected = "WHITE";

    const char* actual = ColorJudge::colorToString(color);

    EXPECT_STREQ(expected, actual);
  }

  TEST(ColorJudgeTest, colorToStringBlue)
  {
    COLOR color = COLOR::BLUE;
    const char* expected = "BLUE";

    const char* actual = ColorJudge::colorToString(color);

    EXPECT_STREQ(expected, actual);
  }

  TEST(ColorJudgeTest, colorToStringGreen)
  {
    COLOR color = COLOR::GREEN;
    const char* expected = "GREEN";

    const char* actual = ColorJudge::colorToString(color);

    EXPECT_STREQ(expected, actual);
  }

  TEST(ColorJudgeTest, colorToStringYellow)
  {
    COLOR color = COLOR::YELLOW;
    const char* expected = "YELLOW";

    const char* actual = ColorJudge::colorToString(color);

    EXPECT_STREQ(expected, actual);
  }

  TEST(ColorJudgeTest, colorToStringRed)
  {
    COLOR color = COLOR::RED;
    const char* expected = "RED";

    const char* actual = ColorJudge::colorToString(color);

    EXPECT_STREQ(expected, actual);
  }

  TEST(ColorJudgeTest, colorToStringNone)
  {
    COLOR color = COLOR::NONE;
    const char* expected = "NONE";

    const char* actual = ColorJudge::colorToString(color);

    EXPECT_STREQ(expected, actual);
  }

}  // namespace etrobocon2022_test
