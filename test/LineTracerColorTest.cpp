/**
 * @file   LineTracerColorTest.cpp
 * @brief  LineTracerColorクラスのテスト
 * @author mutotaka0426 kodama0720
 */

#include "LineTracerColor.h"
#include "Mileage.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2022_test {
  // 最初3回の色取得で連続して指定色を取得するテストケース
  TEST(LineTracerColorTest, runToGetFirst)
  {
    COLOR targetColor = COLOR::GREEN;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    LineTracerColor lc(targetColor, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // 最初2回の色取得分は走行するため，その分の走行距離分を許容誤差とする
    int error = Mileage::calculateMileage(pwm * 0.05 * 2, pwm * 0.05 * 2);  // 許容誤差

    srand(9037);  // 3回連続して緑を取得する乱数シード
    lc.run();     // 緑までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);          // 初期値より少しでも進んでいる
    EXPECT_GE(expected + error, actual);  // 実行後に走行した距離が許容誤差以下である
  }

  // 少し走ってから指定色を取得するテストケース
  TEST(LineTracerColorTest, runLeftEdge)
  {
    COLOR targetColor = COLOR::BLUE;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    LineTracerColor lc(targetColor, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    srand(0);  // 最初に識別する色が青ではない乱数シード
    lc.run();  // 青までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);  // 実行後に少しでも進んでいる
  }

  // 少し走ってから指定色を取得するテストケース
  TEST(LineTracerColorTest, runRightEdge)
  {
    COLOR targetColor = COLOR::RED;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    LineTracerColor lc(targetColor, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    srand(0);  // 最初に識別する色が赤ではない乱数シード
    lc.run();  // 赤までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);  // 実行後に少しでも進んでいる
  }

  // 少し走ってから指定色を取得するテストケース
  TEST(LineTracerColorTest, runBackLeftEdge)
  {
    COLOR targetColor = COLOR::YELLOW;
    double targetBrightness = 45;
    int pwm = -100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    LineTracerColor lc(targetColor, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    srand(0);  // 最初に識別する色が黄ではない乱数シード
    lc.run();  // 黄までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GT(expected, actual);  // 実行後に少しでも進んでいる
  }

  // 少し走ってから指定色を取得するテストケース
  TEST(LineTracerColorTest, runBackRightEdge)
  {
    COLOR targetColor = COLOR::GREEN;
    double targetBrightness = 45;
    int pwm = -100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = false;
    LineTracerColor lc(targetColor, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    srand(0);  // 最初に識別する色が緑ではない乱数シード
    lc.run();  // 緑までライントレースを実行

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GT(expected, actual);  // 実行後に少しでも進んでいる
  }

  TEST(LineTracerColorTest, runZeroPWM)
  {
    COLOR targetColor = COLOR::BLUE;
    double targetBrightness = 45;
    int pwm = 0;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    LineTracerColor lc(targetColor, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to LineTracerColor is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    srand(0);  // 最初に識別する色が青ではない乱数シード
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    lc.run();                            // 青までライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }

  TEST(LineTracerColorTest, runNoneColor)
  {
    COLOR targetColor = COLOR::NONE;
    double targetBrightness = 45;
    int pwm = 100;
    PidGain gain = { 0.1, 0.05, 0.05 };
    bool isLeftEdge = true;
    LineTracerColor lc(targetColor, targetBrightness, pwm, gain, isLeftEdge);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetColor passed to LineTracerColor is NONE";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    lc.run();                            // ライントレースを実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // ライントレース後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  // ライントレース前後で走行距離に変化はない
  }
}  // namespace etrobocon2022_test
