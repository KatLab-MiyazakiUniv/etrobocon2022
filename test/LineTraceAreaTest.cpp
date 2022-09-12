/**
 * @file LineTraceAreaTest.cpp
 * @brief LineTraceAreaクラスのテスト
 * @author mutotaka0426
 */

#include "LineTraceArea.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2022_test {

  TEST(LineTraceAreaTest, runLeftCourse)
  {
    bool isLeftCourse = true;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    LineTraceArea::runLineTraceArea(isLeftCourse, isLeftEdge, targetBrightness);
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;

    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
  }

  TEST(LineTraceAreaTest, runRightCourse)
  {
    bool isLeftCourse = false;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    LineTraceArea::runLineTraceArea(isLeftCourse, isLeftEdge, targetBrightness);
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Warning") == string::npos && output.find("Error") == string::npos;

    EXPECT_TRUE(actual);  // WarningやErrorが出ていないかテスト
  }
}  // namespace etrobocon2022_test
