/**
 *  @file   DistanceTurningTest.cpp
 j  @brief  DistanceTurningクラスのテスト
 *  @author mutotaka0426
 */

#include "DistanceTurning.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include "Controller.h"
#include "Measurer.h"

using namespace std;

namespace etrobocon2022_test {

  TEST(DistanceTurningTest, runRightPivot)
  {
    double targetDistance = 350;
    int leftPwm = 100;
    int rightPwm = 0;
    DistanceTurning dt(targetDistance, leftPwm, rightPwm);
    Measurer measurer;

    // 初期値
    int initialLeftCount = measurer.getLeftCount();
    int initialRightCount = measurer.getRightCount();
    // 期待する走行距離
    double expected = targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error
        = Mileage::calculateMileage(abs(leftPwm * 0.05), abs(rightPwm * 0.05));  // 許容誤差

    dt.run();  // 旋回を実行

    // 関数実行後の走行距離
    int leftCount = abs(initialLeftCount - measurer.getLeftCount());
    int rightCount = abs(initialRightCount - measurer.getRightCount());
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    // 走行距離のテスト
    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  TEST(DistanceTurningTest, runLeftPivot)
  {
    double targetDistance = 350;
    int leftPwm = 0;
    int rightPwm = 100;
    DistanceTurning dt(targetDistance, leftPwm, rightPwm);
    Measurer measurer;

    // 初期値
    int initialLeftCount = measurer.getLeftCount();
    int initialRightCount = measurer.getRightCount();
    // 期待する走行距離
    double expected = targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error
        = Mileage::calculateMileage(abs(leftPwm * 0.05), abs(rightPwm * 0.05));  // 許容誤差

    dt.run();  // 旋回を実行

    // 関数実行後の走行距離
    int leftCount = abs(initialLeftCount - measurer.getLeftCount());
    int rightCount = abs(initialRightCount - measurer.getRightCount());
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    // 走行距離のテスト
    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  TEST(DistanceTurningTest, runBackRight)
  {
    double targetDistance = 1000;
    int leftPwm = -100;
    int rightPwm = -80;
    DistanceTurning dt(targetDistance, leftPwm, rightPwm);
    Measurer measurer;

    // 初期値
    int initialLeftCount = measurer.getLeftCount();
    int initialRightCount = measurer.getRightCount();
    // 期待する走行距離
    double expected = targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error
        = Mileage::calculateMileage(abs(leftPwm * 0.05), abs(rightPwm * 0.05));  // 許容誤差

    dt.run();  // 旋回を実行

    // 関数実行後の走行距離
    int leftCount = abs(initialLeftCount - measurer.getLeftCount());
    int rightCount = abs(initialRightCount - measurer.getRightCount());
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    // 走行距離のテスト
    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  TEST(DistanceTurningTest, runBackLeft)
  {
    double targetDistance = 1000;
    int leftPwm = -80;
    int rightPwm = -100;
    DistanceTurning dt(targetDistance, leftPwm, rightPwm);
    Measurer measurer;

    // 初期値
    int initialLeftCount = measurer.getLeftCount();
    int initialRightCount = measurer.getRightCount();
    // 期待する走行距離
    double expected = targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error
        = Mileage::calculateMileage(abs(leftPwm * 0.05), abs(rightPwm * 0.05));  // 許容誤差

    dt.run();  // 旋回を実行

    // 関数実行後の走行距離
    int leftCount = abs(initialLeftCount - measurer.getLeftCount());
    int rightCount = abs(initialRightCount - measurer.getRightCount());
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    // 走行距離のテスト
    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  TEST(DistanceTurningTest, runZeroPwm)
  {
    double targetDistance = 1000;
    int leftPwm = 0;
    int rightPwm = 0;
    DistanceTurning dt(targetDistance, leftPwm, rightPwm);
    Measurer measurer;

    // 初期値
    int initialLeftCount = measurer.getLeftCount();
    int initialRightCount = measurer.getRightCount();
    // 期待する走行距離
    double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to DistanceTurning is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    dt.run();                            // 旋回を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 関数実行後の走行距離
    int leftCount = measurer.getLeftCount();
    int rightCount = measurer.getRightCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);              // 走行距離のテスト
  }

  TEST(DistanceTurningTest, runMinusDistance)
  {
    double targetDistance = -350;
    int leftPwm = 100;
    int rightPwm = 100;
    DistanceTurning dt(targetDistance, leftPwm, rightPwm);
    Measurer measurer;

    // 初期値
    int initialLeftCount = measurer.getLeftCount();
    int initialRightCount = measurer.getRightCount();
    // 期待する走行距離
    double expected = Mileage::calculateMileage(initialRightCount, initialLeftCount);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetDistance value passed to DistanceTurning is -350.00";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    dt.run();                            // 旋回を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 関数実行後の走行距離
    int leftCount = measurer.getLeftCount();
    int rightCount = measurer.getRightCount();
    double actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);              // 走行距離のテスト
  }

}  // namespace etrobocon2022_test
