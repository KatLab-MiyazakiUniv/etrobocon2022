/**
 * @file Rotation.cpp
 * @brief Roationクラスをテストする
 * @author sugaken0528 KakinokiKanta
 */

#include "Rotation.h"
#include <gtest/gtest.h>
#include <cmath>

namespace etrobocon2022_test {

  constexpr double TRANSFORM = 2.0 * RADIUS / TREAD;

  //左回頭のテスト

  TEST(RotationTest, rotateLeft)
  {
    Measurer measurer;
    Rotation rotation;
    double expectedLeft, expectedRight;
    double actualLeft, actualRight;
    double leftMotorCount;
    double rightMotorCount;
    double targetDistance;
    double error = (M_PI * TREAD / 360) * 3;  //誤差3度
    int angle, pwm;

    // 90度左回頭の回頭誤差が３度未満かテスト
    angle = 90;
    pwm = 30;
    targetDistance = M_PI * TREAD * abs(angle) / 360;
    // 期待する走行距離
    expectedRight = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance;
    // 回頭
    rotation.rotateLeft(angle, pwm);
    // 関数実行後の走行距離
    actualRight = Mileage::calculateWheelMileage(measurer.getRightCount());
    // 誤差のテスト
    EXPECT_LE(expectedRight, actualRight);
    EXPECT_GE(expectedRight + error, actualRight);

    // 180度左回頭の回頭誤差が３度未満かテスト
    angle = 180;
    pwm = 30;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedRight = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance;

    rotation.rotateLeft(angle, pwm);

    actualRight = Mileage::calculateWheelMileage(measurer.getRightCount());

    EXPECT_LE(expectedRight, actualRight);
    EXPECT_GE(expectedRight + error, actualRight);

    // 360度左回頭の回頭誤差が３度未満かテスト
    angle = 360;
    pwm = 30;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedRight = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance;

    rotation.rotateLeft(angle, pwm);

    actualRight = Mileage::calculateWheelMileage(measurer.getRightCount());

    EXPECT_LE(expectedRight, actualRight);
    EXPECT_GE(expectedRight + error, actualRight);
  }

  TEST(RotationTest, rotateLeft_zero)
  {
    Measurer measurer;
    Rotation rotation;
    double expectedLeft, expectedRight;
    double actualLeft, actualRight;
    double leftMotorCount;
    double rightMotorCount;
    double targetDistance;
    double error = (M_PI * TREAD / 360) * 3;  //誤差3度
    int angle, pwm;

    // 0度左回頭のテスト
    angle = 0;
    pwm = 30;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedRight = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance;

    rotation.rotateLeft(angle, pwm);

    actualRight = Mileage::calculateWheelMileage(measurer.getRightCount());

    EXPECT_DOUBLE_EQ(expectedRight, actualRight);
  }

  TEST(RotationTest, rotateLeft_maxpwm)
  {
    Measurer measurer;
    Rotation rotation;
    double expectedLeft, expectedRight;
    double actualLeft, actualRight;
    double leftMotorCount;
    double rightMotorCount;
    double targetDistance;
    double error = (M_PI * TREAD / 360) * 3;  //誤差3度
    int angle, pwm;

    // PWM値が100の時のテスト
    angle = 90;
    pwm = 100;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedRight = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance;

    rotation.rotateLeft(angle, pwm);

    actualRight = Mileage::calculateWheelMileage(measurer.getRightCount());

    EXPECT_LE(expectedRight, actualRight);
    EXPECT_GE(expectedRight + error, actualRight);
  }

  TEST(RotationTest, rotateLeft_minus)
  {
    Measurer measurer;
    Rotation rotation;
    double expectedLeft, expectedRight;
    double actualLeft, actualRight;
    double leftMotorCount;
    double rightMotorCount;
    double targetDistance;
    double error = (M_PI * TREAD / 360) * 3;  //誤差3度
    int angle, pwm;

    // 回転角度がマイナス
    angle = -90;
    pwm = 100;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedRight = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance;

    rotation.rotateLeft(angle, pwm);

    actualRight = Mileage::calculateWheelMileage(measurer.getRightCount());

    EXPECT_LE(expectedRight, actualRight);
    EXPECT_GE(expectedRight + error, actualRight);

    // PWM値がマイナス
    angle = 90;
    pwm = -100;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedRight = Mileage::calculateWheelMileage(measurer.getRightCount()) + targetDistance;

    rotation.rotateLeft(angle, pwm);

    actualRight = Mileage::calculateWheelMileage(measurer.getRightCount());

    EXPECT_LE(expectedRight, actualRight);
    EXPECT_GE(expectedRight + error, actualRight);
  }

  //右回頭のテスト

  TEST(RotationTest, rotateRight)
  {
    Measurer measurer;
    Controller controller;
    Rotation rotation;
    double expectedLeft, expectedRight;
    double actualLeft, actualRight;
    double leftMotorCount;
    double rightMotorCount;
    double targetDistance;
    double error = (M_PI * TREAD / 360) * 3;  //誤差3度
    int angle, pwm;

    // 90度右回頭の回頭誤差が３度未満かテスト
    angle = 90;
    pwm = 30;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedLeft = Mileage::calculateWheelMileage(measurer.getLeftCount()) + targetDistance;

    rotation.rotateRight(angle, pwm);

    actualLeft = Mileage::calculateWheelMileage(measurer.getLeftCount());

    EXPECT_LE(expectedLeft, actualLeft);
    EXPECT_GE(expectedLeft + error, actualLeft);

    // 180度右回頭の回頭誤差が３度未満かテスト
    angle = 180;
    pwm = 30;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedLeft = Mileage::calculateWheelMileage(measurer.getLeftCount()) + targetDistance;

    rotation.rotateRight(angle, pwm);

    actualLeft = Mileage::calculateWheelMileage(measurer.getLeftCount());

    EXPECT_LE(expectedLeft, actualLeft);
    EXPECT_GE(expectedLeft + error, actualLeft);
  }

  TEST(RotationTest, rotateRight_zero)
  {
    Measurer measurer;
    Rotation rotation;
    double expectedLeft, expectedRight;
    double actualLeft, actualRight;
    double leftMotorCount;
    double rightMotorCount;
    double targetDistance;
    double error = (M_PI * TREAD / 360) * 3;  //誤差3度
    int angle, pwm;

    // 0度右回頭のテスト
    angle = 0;
    pwm = 30;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedLeft = Mileage::calculateWheelMileage(measurer.getLeftCount()) + targetDistance;

    rotation.rotateRight(angle, pwm);

    actualLeft = Mileage::calculateWheelMileage(measurer.getLeftCount());

    EXPECT_DOUBLE_EQ(expectedLeft, actualLeft);
  }

  TEST(RotationTest, rotateRight_maxpwm)
  {
    Measurer measurer;
    Rotation rotation;
    double expectedLeft, expectedRight;
    double actualLeft, actualRight;
    double leftMotorCount;
    double rightMotorCount;
    double targetDistance;
    double error = (M_PI * TREAD / 360) * 3;  //誤差3度
    int angle, pwm;

    // PWM値が100の時のテスト
    angle = 90;
    pwm = 100;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedLeft = Mileage::calculateWheelMileage(measurer.getLeftCount()) + targetDistance;

    rotation.rotateRight(angle, pwm);

    actualLeft = Mileage::calculateWheelMileage(measurer.getLeftCount());

    EXPECT_LE(expectedLeft, actualLeft);
    EXPECT_GE(expectedLeft + error, actualLeft);
  }

  TEST(RotationTest, rotateRight_minus)
  {
    Measurer measurer;
    Rotation rotation;
    double expectedLeft, expectedRight;
    double actualLeft, actualRight;
    double leftMotorCount;
    double rightMotorCount;
    double targetDistance;
    double error = (M_PI * TREAD / 360) * 3;  //誤差3度
    int angle, pwm;

    // 回転角度がマイナス
    angle = -90;
    pwm = 100;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedLeft = Mileage::calculateWheelMileage(measurer.getLeftCount()) + targetDistance;

    rotation.rotateRight(angle, pwm);

    actualLeft = Mileage::calculateWheelMileage(measurer.getLeftCount());

    EXPECT_LE(expectedLeft, actualLeft);
    EXPECT_GE(expectedLeft + error, actualLeft);

    // PWM値がマイナス
    angle = 90;
    pwm = -100;
    targetDistance = M_PI * TREAD * abs(angle) / 360;

    expectedLeft = Mileage::calculateWheelMileage(measurer.getLeftCount()) + targetDistance;

    rotation.rotateRight(angle, pwm);

    actualLeft = Mileage::calculateWheelMileage(measurer.getLeftCount());

    EXPECT_LE(expectedLeft, actualLeft);
    EXPECT_GE(expectedLeft + error, actualLeft);
  }

  //左軸前方向ピボットターン

  TEST(RotationTest, leftFrontZero)
  {
    int angle = 0;
    double expected = 0;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  TEST(RotationTest, leftFront45)
  {
    int angle = 45;
    double expected = 45;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  TEST(RotationTest, leftFront90)
  {
    int angle = 90;
    double expected = 90;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  TEST(RotationTest, leftFront135)
  {
    int angle = 135;
    double expected = 135;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  TEST(RotationTest, leftFront180)
  {
    int angle = 180;
    double expected = 180;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  //右軸前方向ピボットターン

  TEST(RotationTest, rightFrontZero)
  {
    int angle = 0;
    double expected = 0;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  TEST(RotationTest, rightFront45)
  {
    int angle = 45;
    double expected = 45;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  TEST(RotationTest, rightFront90)
  {
    int angle = 90;
    double expected = 90;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  TEST(RotationTest, rightFront135)
  {
    int angle = 135;
    double expected = 135;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  TEST(RotationTest, rightFront180)
  {
    int angle = 180;
    double expected = 180;
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnForwardRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (currentRightMotorCount + currentLeftMotorCount) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5.0, actual);
  }

  //左軸後ろピボットターン

  TEST(RotationTest, leftBacktZero)
  {
    int angle = 0;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }

  TEST(RotationTest, leftBack45)
  {
    int angle = -45;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }

  TEST(RotationTest, leftBack90)
  {
    int angle = -90;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }

  TEST(RotationTest, leftBack135)
  {
    int angle = -135;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }

  TEST(RotationTest, leftBack180)
  {
    int angle = -180;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackLeftPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }

  //右軸後ろピボットターン

  TEST(RotationTest, rightBacktZero)
  {
    int angle = 0;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }

  TEST(RotationTest, rightBack45)
  {
    int angle = -45;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }

  TEST(RotationTest, rightBack90)
  {
    int angle = -90;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }

  TEST(RotationTest, rightBack135)
  {
    int angle = -135;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }

  TEST(RotationTest, rightBack180)
  {
    int angle = -180;
    double expected = std::abs(angle);
    double actual;
    Rotation rotation;
    Measurer measurer;
    int initialRightMotorCount = measurer.getRightCount();
    int initialLeftMotorCount = measurer.getLeftCount();

    rotation.turnBackRightPivot(angle, 100);
    double currentRightMotorCount
        = measurer.getRightCount() - static_cast<double>(initialRightMotorCount);
    double currentLeftMotorCount
        = measurer.getLeftCount() - static_cast<double>(initialLeftMotorCount);
    double motorCount = (std::abs(currentRightMotorCount) + std::abs(currentLeftMotorCount)) / 2;

    actual = TRANSFORM * motorCount;
    ASSERT_GE(expected + 5.0, actual);
    ASSERT_LE(expected - 5.0, actual);
  }
}  // namespace etrobocon2022_test
