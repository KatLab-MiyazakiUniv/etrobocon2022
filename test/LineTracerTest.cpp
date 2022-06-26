/**
 * @file LineTracerTest.cpp
 * @brief LineTracerクラスのテスト
 * @author mutotaka0426
 */

#include "LineTracer.h"
#include <math.h>
#include <gtest/gtest.h>

namespace etrobocon2022_test {

  TEST(LineTracerTest, runLeftEdge)
  {
    Measurer measurer;
    bool isLeftEdge = true;
    LineTracer lineTracer(isLeftEdge);
    double targetDistance = 1000;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };

    // ライントレース前のモータ回転数
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();

    // 直線を想定してライントレースを実行
    lineTracer.run(targetDistance, targetBrightness, pwm, gain);

    int rightCount = measurer.getRightCount() - initialRightCount;
    int leftCount = measurer.getLeftCount() - initialLeftCount;
    int actual = std::abs(rightCount - leftCount);  // 両輪の回転差
    int expectedError = 50;                         // 両輪の回転の予測誤差（deg）

    // ライントレース後の両輪の回転差が予測誤差以下である．
    EXPECT_GE(expectedError, actual);
  }

  TEST(LineTracerTest, runRightEdge)
  {
    Measurer measurer;
    bool isLeftEdge = false;
    LineTracer lineTracer(isLeftEdge);
    double targetDistance = 1000;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };

    // ライントレース前のモータ回転数
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();

    // 直線を想定してライントレースを実行
    lineTracer.run(targetDistance, targetBrightness, pwm, gain);

    int rightCount = measurer.getRightCount() - initialRightCount;
    int leftCount = measurer.getLeftCount() - initialLeftCount;
    int actual = std::abs(rightCount - leftCount);  // 両輪の回転差
    int expectedError = 50;                         // 両輪の回転の予測誤差（deg）

    // ライントレース後の両輪の回転差が予測誤差以下である．
    EXPECT_GE(expectedError, actual);
  }

  TEST(LineTracerTest, runZeroPWM)
  {
    Measurer measurer;
    bool isLeftEdge = true;
    LineTracer lineTracer(isLeftEdge);
    double targetDistance = 1000;
    double targetBrightness = 45;
    int pwm = 0;
    PidGain gain = { 0.1, 0.05, 0.05 };

    // ライントレース前のモータ回転数
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();

    // 直線を想定してライントレースを実行
    lineTracer.run(targetDistance, targetBrightness, pwm, gain);

    int rightCount = measurer.getRightCount() - initialRightCount;
    int leftCount = measurer.getLeftCount() - initialLeftCount;
    int actual = std::abs(rightCount - leftCount);  // 両輪の回転差
    int expectedError = 0;                          // 両輪の回転の予測誤差（deg）

    // ライントレース後の両輪の回転差が予測誤差以下である．
    EXPECT_EQ(expectedError, actual);
  }

  TEST(LineTracerTest, runBack)
  {
    Measurer measurer;
    bool isLeftEdge = true;
    LineTracer lineTracer(isLeftEdge);
    double targetDistance = 1000;
    double targetBrightness = 45;
    int pwm = -100;
    PidGain gain = { 0.1, 0.05, 0.05 };

    // ライントレース前のモータ回転数
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();

    // 直線を想定してライントレースを実行
    lineTracer.run(targetDistance, targetBrightness, pwm, gain);

    int rightCount = measurer.getRightCount() - initialRightCount;
    int leftCount = measurer.getLeftCount() - initialLeftCount;
    int actual = std::abs(rightCount - leftCount);  // 両輪の回転差
    int expectedError = 50;                         // 両輪の回転の予測誤差（deg）

    // ライントレース後の両輪の回転差が予測誤差以下である．
    EXPECT_GE(expectedError, actual);
  }

  // ゲッターのテスト
  TEST(LineTracerTest, getIsLeftEdge)
  {
    bool isLeftEdge = true;
    LineTracer lineTracer(isLeftEdge);

    bool expected = isLeftEdge;
    bool actual = lineTracer.getIsLeftEdge();
    EXPECT_EQ(expected, actual);
  }

  // セッターのテスト
  TEST(LineTracerTest, setIsLeftEdge)
  {
    bool isLeftEdge = true;
    LineTracer lineTracer(isLeftEdge);
    lineTracer.setIsLeftEdge(false);

    bool expected = false;
    bool actual = lineTracer.getIsLeftEdge();
    EXPECT_EQ(expected, actual);
  }

  // トグルのテスト
  TEST(LineTracerTest, toggleEdge)
  {
    bool isLeftEdge = true;
    LineTracer lineTracer(isLeftEdge);
    lineTracer.toggleEdge();

    bool expected = !isLeftEdge;
    bool actual = lineTracer.getIsLeftEdge();
    EXPECT_EQ(expected, actual);
  }
}  // namespace etrobocon2022_test
