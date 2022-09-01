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

    testing::internal::CaptureStdout();                      // 標準出力キャプチャ開始
    armfalling.run();                                        // アームの下降を実行
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // アームを下げた後にモータが回転した角度
    int ArmMotorCount = abs(measurer.getArmMotorCount() - initialArmMotorCount);

    EXPECT_LE(expected, ArmMotorCount);
    EXPECT_GE(expected + error, ArmMotorCount);
  }
}  // namespace etrobocon2022_test
