/**
 * @file   ArmFallingTest.cpp
 * @brief  ArmFallingクラスのテスト
 * @author sap2368
 */

#include "ArmFalling.h"
#include <gtest/gtest.h>
#include <cmath>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2022_test {

  TEST(ArmFallingTest, ArmFalling)
  {
    int angle = 60;
    int pwm = 40;
    ArmFalling armfalling(angle, pwm);
    Measurer measurer;

    double expected = angle;  // 指定した角度を期待値とする

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05;  // 許容誤差[deg]

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    armfalling.run();  // アームの下降を実行

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  TEST(ArmFallingTest, ArmFallingZeroPwm)
  {
    int angle = 60;
    int pwm = 0;
    ArmFalling armfalling(angle, pwm);
    Measurer measurer;

    double expected = 0;  // アームを下げない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to ArmFalling is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armfalling.run();                    // アームの下降を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  //アームを下した前後で角度に変化はない
  }

  TEST(ArmFallingTest, ArmFallingMinusPwm)
  {
    int angle = 60;
    int pwm = -40;
    ArmFalling armfalling(angle, pwm);
    Measurer measurer;

    double expected = 0;  // アームを上げない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to ArmFalling is " + to_string(pwm);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armfalling.run();                    // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  //アームを上げた前後で角度に変化はない
  }

  TEST(ArmFallingTest, ArmFallingOverPwm)
  {
    int angle = 60;
    int pwm = 100;
    ArmFalling armfalling(angle, pwm);
    Measurer measurer;

    double expected = angle;  // 指定した角度を期待値とする

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = 60 * 0.05;  // 許容誤差[deg]

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to ArmFalling is " + to_string(pwm);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armfalling.run();                    // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

  TEST(ArmFallingTest, ArmFallingZeroAngle)
  {
    int angle = 0;
    int pwm = 40;
    ArmFalling armfalling(angle, pwm);
    Measurer measurer;

    double expected = 0;  // アームを上げない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The angle value passed to ArmFalling is 0";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armfalling.run();                    // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  //アームを上げた前後で角度に変化はない
  }

  TEST(ArmFallingTest, ArmFallingMinusAngle)
  {
    int angle = -60;
    int pwm = 40;
    ArmFalling armfalling(angle, pwm);
    Measurer measurer;

    double expected = 0;  // アームを上げない

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The angle value passed to ArmFalling is " + to_string(angle);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armfalling.run();                    // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expected, actual);  //アームを上げた前後で角度に変化はない
  }

  TEST(ArmFallingTest, ArmFallingOverAngle)
  {
    int angle = 360;
    int pwm = 40;
    ArmFalling armfalling(angle, pwm);
    Measurer measurer;

    double expected = 60;  // 最大角度を期待値とする

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05;  // 許容誤差[deg]

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The angle value passed to ArmFalling is " + to_string(angle);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // アームを下げる前のモータカウント
    int initialArmMotorCount = measurer.getArmMotorCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    armfalling.run();                    // アームの上昇を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int actual = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_LE(expected, actual);
    EXPECT_GE(expected + error, actual);
  }

}  // namespace etrobocon2022_test
