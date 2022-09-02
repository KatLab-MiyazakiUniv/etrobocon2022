/**
 * @file  ArmRisingTest.cpp
 * @brief  ArmRisingクラスのテスト
 * @author sap2368
 */

#include "ArmRising.h"
#include <gtest/gtest.h>
#include <cmath>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2022_test {

  TEST(ArmRisingTest, ArmRising)
  {
    int angle = 60;
    int pwm = 40;
    ArmRising armrising(angle, pwm);
    Measurer measurer;

    double expected = angle;  // 指定した角度を期待値とする

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05;  // 許容誤差[deg]

    // アームを上げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    armrising.run();  // アームの上昇を実行

    // アームを上げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  TEST(ArmRisingTest, ArmRisingZeroPwm)
  {
    int angle = 60;
    int pwm = 0;
    ArmRising armrising(angle, pwm);
    Measurer measurer;

    double expected = 0;  // アームを上げない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to ArmRising is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armrising.run();                     // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  //アームを上げた前後で角度に変化はない
  }

  TEST(ArmRisingTest, ArmRisingMinusPwm)
  {
    int angle = 60;
    int pwm = -40;
    ArmRising armrising(angle, pwm);
    Measurer measurer;

    double expected = 0;  // アームを上げない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to ArmRising is " + to_string(pwm);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armrising.run();                     // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  //アームを上げた前後で角度に変化はない
  }

  TEST(ArmRisingTest, ArmRisingOverPwm)
  {
    int angle = 60;
    int pwm = 100;
    ArmRising armrising(angle, pwm);
    Measurer measurer;

    double expected = angle;  // 指定した角度を期待値とする

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05;  // 許容誤差[deg]

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to ArmRising is " + to_string(pwm);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armrising.run();                     // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  TEST(ArmRisingTest, ArmRisingZeroAngle)
  {
    int angle = 0;
    int pwm = 40;
    ArmRising armrising(angle, pwm);
    Measurer measurer;

    double expected = 0;  // アームを上げない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The angle value passed to ArmRising is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armrising.run();                     // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  //アームを上げた前後で角度に変化はない
  }

  TEST(ArmRisingTest, ArmRisingMinusAngle)
  {
    int angle = -60;
    int pwm = 40;
    ArmRising armrising(angle, pwm);
    Measurer measurer;

    double expected = 0;  // アームを上げない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The angle value passed to ArmRising is " + to_string(angle);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armrising.run();                     // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  //アームを上げた前後で角度に変化はない
  }

  TEST(ArmRisingTest, ArmRisingOverAngle)
  {
    int angle = 360;
    int pwm = 40;
    ArmRising armrising(angle, pwm);
    Measurer measurer;

    double expected = 60;  // 最大角度を期待値とする

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05;  // 許容誤差[deg]

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The angle value passed to ArmRising is " + to_string(angle);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armrising.run();                     // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

}  // namespace etrobocon2022_test
