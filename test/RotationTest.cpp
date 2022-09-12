/**
 * @file   RotationTest.cpp
 * @brief  Roationクラスのテスト
 * @author sugaken0528 KakinokiKanta mutotaka0426
 */

#include "Rotation.h"
#include <gtest/gtest.h>
#include <cmath>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2022_test {

  // @see https://github.com/KatLab-MiyazakiUniv/etrobocon2022/blob/main/docs/odometry.md
  constexpr double TRANSFORM = 2.0 * RADIUS / TREAD;  // 回頭角度を求める式の係数

  //右回頭のテスト
  TEST(RotationTest, runRight)
  {
    int angle = 90;
    int pwm = 100;
    bool isClockwise = true;
    Rotation rotation(angle, pwm, isClockwise);
    Measurer measurer;

    double expected = angle;  // 指定した回頭角度を期待値とする

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05 * TRANSFORM;  // 許容誤差[deg]

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    rotation.run();                                          // 右回頭を実行
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int rightMotorCount = abs(measurer.getRightCount() - initialRightMotorCount);
    int leftMotorCount = abs(measurer.getLeftCount() - initialLeftMotorCount);
    double actual = ((rightMotorCount + leftMotorCount) * TRANSFORM) / 2;

    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  //左回頭のテスト
  TEST(RotationTest, runLeft)
  {
    int angle = 180;
    int pwm = 100;
    bool isClockwise = false;
    Rotation rotation(angle, pwm, isClockwise);
    Measurer measurer;

    double expected = angle;  // 指定した回頭角度を期待値とする

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05 * TRANSFORM;  // 許容誤差[deg]

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.run();  // 左回頭を実行

    // 回頭後に各モータが回転した角度
    int rightMotorCount = abs(measurer.getRightCount() - initialRightMotorCount);
    int leftMotorCount = abs(measurer.getLeftCount() - initialLeftMotorCount);

    double actual = ((rightMotorCount + leftMotorCount) * TRANSFORM) / 2;

    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  TEST(RotationTest, runZeroPWM)
  {
    int angle = 45;
    int pwm = 0;
    bool isClockwise = true;
    Rotation rotation(angle, pwm, isClockwise);
    Measurer measurer;

    double expected = 0;  // 回頭しない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to Rotation is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    rotation.run();                      // 右回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int rightMotorCount = abs(measurer.getRightCount() - initialRightMotorCount);
    int leftMotorCount = abs(measurer.getLeftCount() - initialLeftMotorCount);
    double actual = ((rightMotorCount + leftMotorCount) * TRANSFORM) / 2;

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);              // 回頭の前後で角度に変化はない
  }

  TEST(RotationTest, runMinusPWM)
  {
    int angle = 45;
    int pwm = -100;
    bool isClockwise = true;
    Rotation rotation(angle, pwm, isClockwise);
    Measurer measurer;

    double expected = 0;  // 回頭しない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to Rotation is " + to_string(pwm);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    rotation.run();                      // 右回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int rightMotorCount = abs(measurer.getRightCount() - initialRightMotorCount);
    int leftMotorCount = abs(measurer.getLeftCount() - initialLeftMotorCount);
    double actual = ((rightMotorCount + leftMotorCount) * TRANSFORM) / 2;

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);              // 回頭の前後で角度に変化はない
  }

  TEST(RotationTest, runZeroAngle)
  {
    int angle = 0;
    int pwm = 100;
    bool isClockwise = true;
    Rotation rotation(angle, pwm, isClockwise);
    Measurer measurer;

    double expected = 0;  // 回頭しない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The angle value passed to Rotation is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    rotation.run();                      // 右回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int rightMotorCount = abs(measurer.getRightCount() - initialRightMotorCount);
    int leftMotorCount = abs(measurer.getLeftCount() - initialLeftMotorCount);
    double actual = ((rightMotorCount + leftMotorCount) * TRANSFORM) / 2;

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);              // 回頭の前後で角度に変化はない
  }

  TEST(RotationTest, runMinusAngle)
  {
    int angle = -180;
    int pwm = 100;
    bool isClockwise = true;
    Rotation rotation(angle, pwm, isClockwise);
    Measurer measurer;

    double expected = 0;  // 回頭しない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The angle value passed to Rotation is " + to_string(angle);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    rotation.run();                      // 右回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int rightMotorCount = abs(measurer.getRightCount() - initialRightMotorCount);
    int leftMotorCount = abs(measurer.getLeftCount() - initialLeftMotorCount);
    double actual = ((rightMotorCount + leftMotorCount) * TRANSFORM) / 2;

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);              // 回頭の前後で角度に変化はない
  }

  TEST(RotationTest, runOverAngle)
  {
    int angle = 360;
    int pwm = 100;
    bool isClockwise = true;
    Rotation rotation(angle, pwm, isClockwise);
    Measurer measurer;

    double expected = 0;  // 回頭しない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The angle value passed to Rotation is " + to_string(angle);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    rotation.run();                      // 右回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int rightMotorCount = abs(measurer.getRightCount() - initialRightMotorCount);
    int leftMotorCount = abs(measurer.getLeftCount() - initialLeftMotorCount);
    double actual = ((rightMotorCount + leftMotorCount) * TRANSFORM) / 2;

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);              // 回頭の前後で角度に変化はない
  }
}  // namespace etrobocon2022_test
