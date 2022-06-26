/**
 * @file GameMotionParserTest.cpp
 * @brief GameMotionParserクラスをテストする
 * @author miyashita64, kawano
 */

#include "GameMotionParser.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {
  TEST(GameMotionParserTest, readGameMotionFile)
  {
    // シミュレータ環境、GoogleTest では、ファイル読み込みができない
    int expected = -1;
    int actual = GameMotionParser::readGameMotionFile();
    EXPECT_EQ(expected, actual);
  }
}  // namespace etrobocon2022_test
