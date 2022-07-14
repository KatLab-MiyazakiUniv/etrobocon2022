/**
 * @file CalibratorTest.cpp
 * @brief Calibratorクラスのテスト
 * @author mutotaka0426
 */

#include "Calibrator.h"
#include <string>
#include <gtest/gtest.h>

namespace etrobocon2022_test {

  // runを呼び出すだけのテスト
  TEST(CalibratorTest, run)
  {
    Calibrator calibrator;
    calibrator.run();
  }

  // waitForStartを呼び出すだけのテスト
  TEST(CalibratorTest, waitForStart)
  {
    Calibrator calibrator;
    calibrator.waitForStart();
  }

  // ゲッターのテスト
  TEST(CalibratorTest, getIsLeftCourse)
  {
    Calibrator calibrator;
    calibrator.run();

    // 値がランダムに決定されるので標準出力で確認する
    // isLeftCourseの確認
    bool isLeftCourseActual = calibrator.getIsLeftCourse();
    std::string str = isLeftCourseActual ? "true" : "false";
    printf("isLeftCourse = %s\n", str.c_str());

    // targetBrightnessの確認
    int targetBrightnessActual = calibrator.getTargetBrightness();
    printf("targetBrightness = %d\n", targetBrightnessActual);
  }
}  // namespace etrobocon2022_test
