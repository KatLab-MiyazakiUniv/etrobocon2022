/**
 *  @file   StraightRunnerColorTest.cpp
 *  @brief  StraightRunnerColorクラスのテスト
 *  @author sugaken0528 mutotaka0426
 */

#include <gtest/gtest.h>
#include "Measurer.h"
#include "Mileage.h"
#include "StraightRunnerColor.h"

using namespace std;

namespace etrobocon2022_test {
  // 最初の色取得で指定色を取得するテストケース
  TEST(StraightRunnerColorTest, runToGetFirst)
  {
    COLOR targetColor = COLOR::GREEN;
    int pwm = 100;
    StraightRunnerColor sc(targetColor, pwm);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    srand(9037);  // 最初に緑を取得する乱数シード
    sc.run();     // 緑まで直進を実行

    // 直進後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expected, actual);  // 直進前後で走行距離に変化はない
  }

  // 少し走ってから指定色を取得するテストケース
  TEST(StraightRunnerColorTest, run)
  {
    COLOR targetColor = COLOR::BLUE;
    int pwm = 100;
    StraightRunnerColor sc(targetColor, pwm);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    /**
     * 最初10回の色取得分の走行距離を許容誤差とする
     * 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
     * StraightRunnerのPWM値は100まで加速するので，許容誤差のpwmは100で計算する
     */
    int error = Mileage::calculateMileage(100 * 0.05 * 10, 100 * 0.05 * 10);  // 許容誤差

    srand(89);  // 最初10回が青を取得しない乱数シード
    sc.run();   // 青まで直進を実行

    // 直進後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LT(expected, actual);          // 実行後に少しでも進んでいる
    EXPECT_GE(expected + error, actual);  // 直進後の走行距離が許容誤差以内である
  }

  // 少し走ってから指定色を取得するテストケース
  TEST(StraightRunnerColorTest, runBack)
  {
    COLOR targetColor = COLOR::RED;
    int pwm = -100;
    StraightRunnerColor sc(targetColor, pwm);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    /**
     * 最初10回の色取得分の走行距離を許容誤差とする
     * 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
     * StraightRunnerのPWM値は-100まで加速するので，許容誤差のpwmは-100で計算する
     */
    int error = Mileage::calculateMileage(-100 * 0.05 * 10, -100 * 0.05 * 10);  // 許容誤差

    srand(0);  // 最初10回が赤を取得しない乱数シード
    sc.run();  // 赤まで直進を実行

    // 直進後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_GT(expected, actual);          // 実行後に少しでも進んでいる
    EXPECT_LE(expected + error, actual);  // 直進後の走行距離が許容誤差以内である
  }

  TEST(StraightRunnerColorTest, runZeroPWM)
  {
    COLOR targetColor = COLOR::YELLOW;
    int pwm = 0;
    StraightRunnerColor sc(targetColor, pwm);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to StraightRunnerColor is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    srand(0);                            // 最初に黄を取得しない乱数シード
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    sc.run();                            // 黄まで直進を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 直進後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);              // 直進前後で走行距離に変化はない
  }

  TEST(StraightRunnerColorTest, runNoneColor)
  {
    COLOR targetColor = COLOR::NONE;
    int pwm = 100;
    StraightRunnerColor sc(targetColor, pwm);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int initialRightCount = measurer.getRightCount();
    int initialLeftCount = measurer.getLeftCount();
    int expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetColor passed to StraightRunnerColor is NONE";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    sc.run();                            // 黄まで直進を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 直進後の走行距離
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);              // 直進前後で走行距離に変化はない
  }

}  // namespace etrobocon2022_test
