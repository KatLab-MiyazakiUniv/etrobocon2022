/**
 * @file   CorrectingRotationTest.cpp
 * @brief  CorrectingRoationクラスのテスト
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

    // rearCamera.shで-4.1を返すように書き換える
    system("echo \"#!/bin/bash\" > ./etrobocon2022/scripts/rear_camera.sh");
    system("echo \"echo -4.1\" >> ./etrobocon2022/scripts/rear_camera.sh");

    // 期待する車輪ごとの回頭角度(時計回り)
    double expectedLeft = 4;
    double expectedRight = -4;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = pwm * 0.05 * TRANSFORM;  // 許容誤差[deg]

    // 回頭前のモータカウント
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    // testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    xRotation.run();  // 角度補正回頭を実行
    // string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

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
}  // namespace etrobocon2022_test
