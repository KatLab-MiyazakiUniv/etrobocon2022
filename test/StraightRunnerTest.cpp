/**
 *  @file   StraightRunnerTest.cpp
 *  @brief  StraightRunnerクラスのテストファイル
 *  @author sugaken0528
 */

#include <gtest/gtest.h>
#include "Controller.h"
#include "Measurer.h"
#include "StraightRunner.h"

using namespace std;

namespace etrobocon2022_test {

  TEST(StraightRunnerTest, run)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, actualDistance;
    double leftAngle, rightAngle;
    double leftInitial, rightInitial;
    double leftActual, rightActual;
    double leftDifference, rightDifference;

    double targetDistance = 350;
    int pwm = 50;
    double distanceError = 3.0;
    double expectedError = 1.0;
    double actualError;

    // 初期値
    rightAngle = measurer.getRightCount();
    leftAngle = measurer.getLeftCount();
    leftInitial = Mileage::calculateWheelMileage(leftAngle);
    rightInitial = Mileage::calculateWheelMileage(rightAngle);
    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(rightAngle, leftAngle) + targetDistance;
    // 直進
    straightRunner.run(targetDistance, pwm);
    // 関数実行後の走行距離
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftActual = Mileage::calculateWheelMileage(leftAngle);
    rightActual = Mileage::calculateWheelMileage(rightAngle);
    actualDistance = Mileage::calculateMileage(rightAngle, leftAngle);
    // 左右の走行距離
    leftDifference = std::abs(leftActual - leftInitial);
    rightDifference = std::abs(rightActual - rightInitial);
    // 左右の走行距離の誤差
    actualError = std::abs(leftDifference - rightDifference);
    // 走行距離のテスト
    EXPECT_LE(expectedDistance, actualDistance);
    EXPECT_GE(expectedDistance + distanceError, actualDistance);
    // 直進できているかのテスト
    EXPECT_GE(expectedError, actualError);
  }

  TEST(StraightRunnerTest, runFullPwm)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, actualDistance;
    double leftAngle, rightAngle;
    double leftInitial, rightInitial;
    double leftActual, rightActual;
    double leftDifference, rightDifference;

    double targetDistance = 350;
    int pwm = 100;
    double distanceError = 3.5;
    double expectedError = 1.0;
    double actualError;

    // 初期値
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftInitial = Mileage::calculateWheelMileage(leftAngle);
    rightInitial = Mileage::calculateWheelMileage(rightAngle);
    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(rightAngle, leftAngle) + targetDistance;
    // 直進
    straightRunner.run(targetDistance, pwm);
    // 関数実行後の走行距離
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftActual = Mileage::calculateWheelMileage(leftAngle);
    rightActual = Mileage::calculateWheelMileage(rightAngle);
    actualDistance = Mileage::calculateMileage(rightAngle, leftAngle);
    // 左右の走行距離
    leftDifference = std::abs(leftActual - leftInitial);
    rightDifference = std::abs(rightActual - rightInitial);
    // 左右の走行距離の誤差
    actualError = std::abs(leftDifference - rightDifference);
    // 走行距離のテスト
    EXPECT_LE(expectedDistance, actualDistance);
    EXPECT_GE(expectedDistance + distanceError, actualDistance);
    // 直進できているかのテスト
    EXPECT_GE(expectedError, actualError);
  }

  TEST(StraightRunnerTest, runZero)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, actualDistance;

    double targetDistance = 0;
    int pwm = 100;

    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount())
                       + targetDistance;
    // 直進
    straightRunner.run(targetDistance, pwm);
    // 関数実行後の走行距離
    actualDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 走行距離のテスト
    EXPECT_EQ(expectedDistance, actualDistance);
  }

  TEST(StraightRunnerTest, runMinusPwm)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, actualDistance;
    double leftAngle, rightAngle;
    double leftInitial, rightInitial;
    double leftActual, rightActual;
    double leftDifference, rightDifference;

    double targetDistance = 350;
    int pwm = -50;
    double distanceError = 3.0;
    double expectedError = 1.0;
    double actualError;

    // 初期値
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftInitial = Mileage::calculateWheelMileage(leftAngle);
    rightInitial = Mileage::calculateWheelMileage(rightAngle);
    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(rightAngle, leftAngle) - targetDistance;
    // 直進
    straightRunner.run(targetDistance, pwm);
    // 関数実行後の走行距離
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftActual = Mileage::calculateWheelMileage(leftAngle);
    rightActual = Mileage::calculateWheelMileage(rightAngle);
    actualDistance = Mileage::calculateMileage(rightAngle, leftAngle);
    // 左右の走行距離
    leftDifference = std::abs(leftActual - leftInitial);
    rightDifference = std::abs(rightActual - rightInitial);
    // 左右の走行距離の誤差
    actualError = std::abs(leftDifference - rightDifference);
    // 走行距離のテスト
    EXPECT_GE(expectedDistance, actualDistance);
    EXPECT_LE(expectedDistance - distanceError, actualDistance);

    // 直進できているかのテスト
    EXPECT_GE(expectedError, actualError);
  }

  TEST(StraightRunnerTest, runMinusFullPwm)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, actualDistance;
    double leftAngle, rightAngle;
    double leftInitial, rightInitial;
    double leftActual, rightActual;
    double leftDifference, rightDifference;

    double targetDistance = 350;
    int pwm = -100;
    double distanceError = 3.5;
    double expectedError = 1.0;
    double actualError;

    // 初期値
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftInitial = Mileage::calculateWheelMileage(leftAngle);
    rightInitial = Mileage::calculateWheelMileage(rightAngle);
    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(rightAngle, leftAngle) - targetDistance;
    // 直進
    straightRunner.run(targetDistance, pwm);
    // 関数実行後の走行距離
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftActual = Mileage::calculateWheelMileage(leftAngle);
    rightActual = Mileage::calculateWheelMileage(rightAngle);
    actualDistance = Mileage::calculateMileage(rightAngle, leftAngle);
    // 左右の走行距離
    leftDifference = std::abs(leftActual - leftInitial);
    rightDifference = std::abs(rightActual - rightInitial);
    // 左右の走行距離の誤差
    actualError = std::abs(leftDifference - rightDifference);
    // 走行距離のテスト
    EXPECT_GE(expectedDistance, actualDistance);
    EXPECT_LE(expectedDistance - distanceError, actualDistance);
    // 直進できているかのテスト
    EXPECT_GE(expectedError, actualError);
  }

  TEST(StraightRunnerTest, runPwmZero)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, actualDistance;

    double targetDistance = 350;
    int pwm = 0;

    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 直進
    straightRunner.run(targetDistance, pwm);
    // 関数実行後の走行距離
    actualDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 走行距離のテスト
    EXPECT_EQ(expectedDistance, actualDistance);
  }

  TEST(StraightRunnerTest, runStraightToMinusDistancePwmZero)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, actualDistance;

    double targetDistance = -350;
    int pwm = 0;

    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 直進
    straightRunner.run(targetDistance, pwm);
    // 関数実行後の走行距離
    actualDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 走行距離のテスト
    EXPECT_EQ(expectedDistance, actualDistance);
  }
}  // namespace etrobocon2022_test
