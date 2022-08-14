/**
 * @file   MotionTest.cpp
 * @brief  Motionクラスのテスト
 * @author mutotaka0426
 */

#include "MotionChild.h"
#include "Measurer.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

namespace etrobocon2022_test {

  TEST(MotionTest, run)
  {
    double targetDistance = 1000;
    int pwm = 100;
    MotionChild motionChild(targetDistance, pwm);
    Measurer measurer;

    // 初期値から期待する走行距離を求める
    int rightCount = measurer.getRightCount();
    int leftCount = measurer.getLeftCount();
    double expected = Mileage::calculateMileage(rightCount, leftCount) + targetDistance;

    // 一回のsetPWM()でダミーのモータカウントに加算される値はpwm * 0.05
    double error = Mileage::calculateMileage(pwm * 0.05, pwm * 0.05);  // 許容誤差

    // 旋回の実行
    motionChild.run();

    // 旋回後の走行距離
    rightCount = measurer.getRightCount();
    leftCount = measurer.getLeftCount();
    int actual = Mileage::calculateMileage(rightCount, leftCount);

    EXPECT_LE(expected, actual);  // 旋回後に走行した距離が期待する走行距離以上である
    EXPECT_GE(expected + error, actual);  // 旋回後に走行した距離が許容誤差以内である
  }

  TEST(MotionTest, logRunning)
  {
    double targetDistance = 100;
    int pwm = 50;
    MotionChild motionChild(targetDistance, pwm);

    const int BUF_SIZE = 256;
    char expected[BUF_SIZE];  // log用にメッセージを一時保存する
    sprintf(expected, "Run MotionChild (targetDistance: %.2f, pwm: %d)\n", targetDistance, pwm);

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    motionChild.logRunning();
    std::string actual = testing::internal::GetCapturedStdout();  // キャプチャ終了

    ASSERT_STREQ(expected, actual.c_str());
  }

}  // namespace etrobocon2022_test
