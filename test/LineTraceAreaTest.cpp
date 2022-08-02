/**
 * @file LineTraceAreaTest.cpp
 * @brief LineTraceAreaクラスのテスト
 * @author mutotaka0426
 */

#include "LineTraceArea.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {

  // Lコースで呼び出すだけのテスト
  TEST(LineTraceAreaTest, runLeftCourse)
  {
    bool isLeftCourse = true;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;
    LineTraceArea::runLineTraceArea(isLeftCourse, isLeftEdge, targetBrightness);
  }

  // Rコースで呼び出すだけのテスト
  TEST(LineTraceAreaTest, runRightCourse)
  {
    bool isLeftCourse = false;
    bool isLeftEdge = isLeftCourse;
    int targetBrightness = 45;
    LineTraceArea::runLineTraceArea(isLeftCourse, isLeftEdge, targetBrightness);
  }
}  // namespace etrobocon2022_test
