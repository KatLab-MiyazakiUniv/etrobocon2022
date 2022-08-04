/**
 * @file LineTracerTest.cpp
 * @brief LineTracerクラスのテスト
 * @author mutotaka0426 kodama0720
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

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount) + targetDistance;
    int error = 10;  // 許容誤差

    // ライントレースを実行
    lineTracer.run(targetDistance, targetBrightness, pwm, gain);

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以上である
    EXPECT_GE(expected + error, actual);  // ライントレース後に走行した距離が許容誤差以内である
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

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount) + targetDistance;
    int error = 10;  // 許容誤差

    // ライントレースを実行
    lineTracer.run(targetDistance, targetBrightness, pwm, gain);

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以上である
    EXPECT_GE(expected + error, actual);  // ライントレース後に走行した距離が許容誤差以内である
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

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // ライントレースを実行
    lineTracer.run(targetDistance, targetBrightness, pwm, gain);

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
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

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount) - targetDistance;
    int error = 10;  // 許容誤差

    // ライントレースを実行
    lineTracer.run(targetDistance, targetBrightness, pwm, gain);

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以下である
    EXPECT_LE(expected - error, actual);  // ライントレース後に走行した距離が許容誤差以内である
  }

  TEST(LineTracerTest, runToColor)
  {
    Measurer measurer;
    bool isLeftEdge = true;
    LineTracer lineTracer(isLeftEdge);
    COLOR targetColor = COLOR::GREEN;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // 緑までライントレースを実行
    lineTracer.runToColor(targetColor, targetBrightness, pwm, gain);

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LE(expected, actual);  // 初期値より0cm以上進んでいる
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

    bool expected = false;
    bool actual = lineTracer.getIsLeftEdge();
    EXPECT_EQ(expected, actual);
  }
}  // namespace etrobocon2022_test
