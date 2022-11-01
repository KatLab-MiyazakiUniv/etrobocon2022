/**
 * @file   GameAreaTest.cpp
 * @brief  GameAreaクラスのテスト
 * @author mutotaka0426
 */

#include "GameArea.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2022_test {

  TEST(GameAreaTest, runLeftCourse)
  {
    bool isLeftCourse = true;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    GameArea::runGameArea(isLeftCourse, isLeftEdge, targetBrightness);  // 実行
    string output = testing::internal::GetCapturedStdout();             // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;

    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
  }

  TEST(GameAreaTest, runRightCourse)
  {
    bool isLeftCourse = false;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    GameArea::runGameArea(isLeftCourse, isLeftEdge, targetBrightness);  // 実行
    string output = testing::internal::GetCapturedStdout();             // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;

    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
  }
}  // namespace etrobocon2022_test
