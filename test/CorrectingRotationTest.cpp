/**
 * @file   CorrectingRotationTest.cpp
 * @brief  CorrectingRotationクラスのテスト
 * @author mutotaka0426 kawanoichi
 */

#include "CorrectingRotation.h"
#include <gtest/gtest.h>
#include <cmath>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2022_test {

  // @see https://github.com/KatLab-MiyazakiUniv/etrobocon2022/blob/main/docs/odometry.md
  constexpr double TRANSFORM = 2.0 * RADIUS / TREAD;  // 回頭角度を求める式の係数

  // 0度を目標に時計回りの角度補正をするテスト
  TEST(CorrectingRotationTest, runClockwiseToZero)
  {
    int targetAngle = 0;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで-2.1を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo -2.1\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // 期待する車輪ごとの回頭角度(時計回り)
    double expectedLeft = 2;
    double expectedRight = -2;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05 * TRANSFORM;  // 許容誤差[deg]

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    xRotation.run();                                         // 角度補正回頭を実行
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 左車輪のテスト
    EXPECT_LE(expectedLeft, actualLeft);
    EXPECT_GE(expectedLeft + error, actualLeft);
    // 右車輪のテスト
    EXPECT_GE(expectedRight, actualRight);
    EXPECT_LE(expectedRight - error, actualRight);
  }

  // 0度を目標に反時計回りの角度補正をするテスト
  TEST(CorrectingRotationTest, runAnticlockwiseToZero)
  {
    int targetAngle = 0;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで5.9を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo 5.9\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // 期待する車輪ごとの回頭角度(時計回り)
    double expectedLeft = -5;
    double expectedRight = 5;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05 * TRANSFORM;  // 許容誤差[deg]

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    xRotation.run();                                         // 角度補正回頭を実行
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 左車輪のテスト
    EXPECT_GE(expectedLeft, actualLeft);
    EXPECT_LE(expectedLeft - error, actualLeft);
    // 右車輪のテスト
    EXPECT_LE(expectedRight, actualRight);
    EXPECT_GE(expectedRight + error, actualRight);
  }

  // 45度を目標に時計回りの角度補正をするテスト
  TEST(CorrectingRotationTest, runClockwiseTo45)
  {
    int targetAngle = 45;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで-49.9を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo -49.9\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // 期待する車輪ごとの回頭角度(時計回り)
    double expectedLeft = 4;
    double expectedRight = -4;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05 * TRANSFORM;  // 許容誤差[deg]

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    xRotation.run();                                         // 角度補正回頭を実行
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 左車輪のテスト
    EXPECT_LE(expectedLeft, actualLeft);
    EXPECT_GE(expectedLeft + error, actualLeft);
    // 右車輪のテスト
    EXPECT_GE(expectedRight, actualRight);
    EXPECT_LE(expectedRight - error, actualRight);
  }

  // 45度を目標に反時計回りの角度補正をするテスト
  TEST(CorrectingRotationTest, runAnticlockwiseTo45)
  {
    int targetAngle = 45;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで50.1を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo 50.1\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // 期待する車輪ごとの回頭角度(時計回り)
    double expectedLeft = -5;
    double expectedRight = 5;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05 * TRANSFORM;  // 許容誤差[deg]

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    xRotation.run();                                         // 角度補正回頭を実行
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 左車輪のテスト
    EXPECT_GE(expectedLeft, actualLeft);
    EXPECT_LE(expectedLeft - error, actualLeft);
    // 右車輪のテスト
    EXPECT_LE(expectedRight, actualRight);
    EXPECT_GE(expectedRight + error, actualRight);
  }

  // 0度を目標に時計回りの角度補正をするテスト（縦線を取得できなかった場合）
  TEST(CorrectingRotationTest, runClockwiseTo90)
  {
    int targetAngle = 0;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで87.9を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo 87.9\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // 期待する車輪ごとの回頭角度(時計回り)
    double expectedLeft = 2;
    double expectedRight = -2;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05 * TRANSFORM;  // 許容誤差[deg]

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    xRotation.run();                                         // 角度補正回頭を実行
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 左車輪のテスト
    EXPECT_LE(expectedLeft, actualLeft);
    EXPECT_GE(expectedLeft + error, actualLeft);
    // 右車輪のテスト
    EXPECT_GE(expectedRight, actualRight);
    EXPECT_LE(expectedRight - error, actualRight);
  }

  // 0度を目標に反時計回りの角度補正をするテスト（縦線を取得できなかった場合）
  TEST(CorrectingRotationTest, runAnticlockwiseTo90)
  {
    int targetAngle = 0;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで-85.1を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo -85.1\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // 期待する車輪ごとの回頭角度(時計回り)
    double expectedLeft = -4;
    double expectedRight = 4;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05 * TRANSFORM;  // 許容誤差[deg]

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    xRotation.run();                                         // 角度補正回頭を実行
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 左車輪のテスト
    EXPECT_GE(expectedLeft, actualLeft);
    EXPECT_LE(expectedLeft - error, actualLeft);
    // 右車輪のテスト
    EXPECT_LE(expectedRight, actualRight);
    EXPECT_GE(expectedRight + error, actualRight);
  }

  // 補正免除される場合のテスト
  TEST(CorrectingRotationTest, runNoCorrecting)
  {
    int targetAngle = 0;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで-2.0を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo -2.0\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // 期待する車輪ごとの回頭角度(時計回り)
    double expectedLeft = 0;
    double expectedRight = 0;

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    xRotation.run();                                         // 角度補正回頭を実行
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 左車輪のテスト
    EXPECT_EQ(expectedLeft, actualLeft);
    // 右車輪のテスト
    EXPECT_EQ(expectedRight, actualRight);
  }

  TEST(CorrectingRotationTest, runZeroPWM)
  {
    int targetAngle = 0;
    int pwm = 0;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで-5.0を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo -5.0\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to CorrectingRotation is " + to_string(pwm);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 期待する車輪ごとの回頭角度
    double expectedLeft = 0;
    double expectedRight = 0;

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    xRotation.run();                     // 角度補正回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 補正の前後で角度に変化はない
    EXPECT_EQ(expectedLeft, actualLeft);
    EXPECT_EQ(expectedRight, actualRight);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
  }

  TEST(CorrectingRotationTest, runMinusPWM)
  {
    int targetAngle = 0;
    int pwm = -100;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで-5.0を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo -5.0\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The pwm value passed to CorrectingRotation is " + to_string(pwm);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 期待する車輪ごとの回頭角度
    double expectedLeft = 0;
    double expectedRight = 0;

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    xRotation.run();                     // 角度補正回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 補正の前後で角度に変化はない
    EXPECT_EQ(expectedLeft, actualLeft);
    EXPECT_EQ(expectedRight, actualRight);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
  }

  TEST(CorrectingRotationTest, runMinusAngle)
  {
    int targetAngle = -1;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで-5.0を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo -5.0\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetAngle value passed to CorrectingRotation is "
                      + to_string(targetAngle);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 期待する車輪ごとの回頭角度
    double expectedLeft = 0;
    double expectedRight = 0;

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    xRotation.run();                     // 角度補正回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 補正の前後で角度に変化はない
    EXPECT_EQ(expectedLeft, actualLeft);
    EXPECT_EQ(expectedRight, actualRight);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
  }

  TEST(CorrectingRotationTest, runOverAngle)
  {
    int targetAngle = 90;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shで-5.0を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo -5.0\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: The targetAngle value passed to CorrectingRotation is "
                      + to_string(targetAngle);
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 期待する車輪ごとの回頭角度
    double expectedLeft = 0;
    double expectedRight = 0;

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    xRotation.run();                     // 角度補正回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 補正の前後で角度に変化はない
    EXPECT_EQ(expectedLeft, actualLeft);
    EXPECT_EQ(expectedRight, actualRight);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
  }

  // rear_camera.shがNoneを返した場合
  TEST(CorrectingRotationTest, runReturnNone)
  {
    int targetAngle = 45;
    int pwm = 60;
    CorrectingRotation xRotation(targetAngle, pwm);
    Measurer measurer;

    // rearCamera.shでNoneを返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo \"None\"\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: Could not recognize black line";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // 期待する車輪ごとの回頭角度
    double expectedLeft = 0;
    double expectedRight = 0;

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    xRotation.run();                     // 角度補正回頭を実行
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // 回頭後に各モータが回転した角度
    int actualLeft = (measurer.getLeftCount() - initialLeftMotorCount) * TRANSFORM;
    int actualRight = (measurer.getRightCount() - initialRightMotorCount) * TRANSFORM;

    // 補正の前後で角度に変化はない
    EXPECT_EQ(expectedLeft, actualLeft);
    EXPECT_EQ(expectedRight, actualRight);

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
  }
}  // namespace etrobocon2022_test
