/**
 * @file   DistanceLineTracingTest.cpp
 * @brief  DistanceLineTracingクラスのテスト
 * @author mutotaka0426 kodama0720
 */

#include "DistanceLineTracing.h"
#include "Measurer.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2022_test {

  TEST(DistanceLineTracingTest, runLeftEdge)
  {
    double targetDistance = 1000;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    DistanceLineTracing dl(targetDistance, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    double expected
        = Mileage::calculateMileage(initialRightCount, initialLeftCount) + targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = Mileage::calculateMileage(pwm * 0.05, pwm * 0.05);  // 許容誤差

    dl.run();  // ライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以上である
    EXPECT_GT(expected + error, actual);  // ライントレース後に走行した距離が許容誤差未満である
  }

  TEST(DistanceLineTracingTest, runRightEdge)
  {
    double targetDistance = 1000;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    DistanceLineTracing dl(targetDistance, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    double expected
        = Mileage::calculateMileage(initialRightCount, initialLeftCount) + targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = Mileage::calculateMileage(pwm * 0.05, pwm * 0.05);  // 許容誤差

    dl.run();  // ライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以上である
    EXPECT_GT(expected + error, actual);  // ライントレース後に走行した距離が許容誤差未満である
  }

  TEST(DistanceLineTracingTest, runBackLeftEdge)
  {
    double targetDistance = 1000;
    double targetBrightness = 45;
    int pwm = -100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    DistanceLineTracing dl(targetDistance, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    double expected
        = Mileage::calculateMileage(initialRightCount, initialLeftCount) - targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error
        = Mileage::calculateMileage(std::abs(pwm * 0.05), std::abs(pwm * 0.05));  // 許容誤差

    dl.run();  // ライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以下である
    EXPECT_LT(expected - error, actual);  // ライントレース後に走行した距離が許容誤差未満である
  }

  TEST(DistanceLineTracingTest, runBackRightEdge)
  {
    double targetDistance = 1000;
    double targetBrightness = 45;
    int pwm = -100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    DistanceLineTracing dl(targetDistance, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    double expected
        = Mileage::calculateMileage(initialRightCount, initialLeftCount) - targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error
        = Mileage::calculateMileage(std::abs(pwm * 0.05), std::abs(pwm * 0.05));  // 許容誤差

    dl.run();  // ライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GE(expected, actual);  // ライントレース後に走行した距離が期待する走行距離以下である
    EXPECT_LT(expected - error, actual);  // ライントレース後に走行した距離が許容誤差未満である
  }

  TEST(DistanceLineTracingTest, runZeroPWM)
  {
    double targetDistance = 1000;
    double targetBrightness = 45;
    int pwm = 0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    DistanceLineTracing dl(targetDistance, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to DistanceLineTracing is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    dl.run();                            // ライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }

  TEST(DistanceLineTracingTest, runMinusDistance)
  {
    double targetDistance = -1000;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    DistanceLineTracing dl(targetDistance, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetDistance value passed to DistanceLineTracing is -1000.00";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    dl.run();                            // ライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }
}  // namespace etrobocon2022_test
