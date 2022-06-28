/**
 *  @file   StraightRunnerTest.cpp
 *  @brief  StraightRunnerクラスのテストファイル
 *  @author mutotaka0426
 */

#include <gtest/gtest.h>
#include "Controller.h"
#include "Measurer.h"
#include "StraightRunner.h"

using namespace std;

namespace etrobocon2022_test {

  TEST(runStraightToDistanceTest, runStraightToDistance)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, currentDistance;
    double leftAngle, rightAngle;
    double leftInitial, rightInitial;
    double leftActual, rightActual;
    double leftDifference, rightDifference;

    double targetDistance = 350;
    int pwm = 50;
    double distanceError = 3.0, differenceError = 1.0;

    // 初期値
    rightAngle = measurer.getRightCount();
    leftAngle = measurer.getLeftCount();
    leftInitial = Mileage::calculateWheelMileage(leftAngle);
    rightInitial = Mileage::calculateWheelMileage(rightAngle);
    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(rightAngle, leftAngle) + targetDistance;
    // 直進
    straightRunner.runStraightToDistance(targetDistance, pwm);
    // 関数実行後の走行距離
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftActual = Mileage::calculateWheelMileage(leftAngle);
    rightActual = Mileage::calculateWheelMileage(rightAngle);
    currentDistance = Mileage::calculateMileage(rightAngle, leftAngle);
    // 左右の進行距離
    leftDifference = std::abs(leftActual - leftInitial);
    rightDifference = std::abs(rightActual - rightInitial);
    // 走行距離のテスト
    EXPECT_LE(expectedDistance, currentDistance);
    EXPECT_GE(expectedDistance + distanceError, currentDistance);
    // 直進できているかのテスト
    EXPECT_GE(differenceError, std::abs(leftDifference - rightDifference));
  }

  TEST(runStraightToDistanceTest, runStraightToDistanceFullPwm)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, currentDistance;
    double leftAngle, rightAngle;
    double leftInitial, rightInitial;
    double leftActual, rightActual;
    double leftDifference, rightDifference;

    double targetDistance = 350;
    int pwm = 100;
    double distanceError = 3.5, differenceError = 1.0;

    // 初期値
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftInitial = Mileage::calculateWheelMileage(leftAngle);
    rightInitial = Mileage::calculateWheelMileage(rightAngle);
    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(rightAngle, leftAngle) + targetDistance;
    // 直進
    straightRunner.runStraightToDistance(targetDistance, pwm);
    // 関数実行後の走行距離
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftActual = Mileage::calculateWheelMileage(leftAngle);
    rightActual = Mileage::calculateWheelMileage(rightAngle);
    currentDistance = Mileage::calculateMileage(rightAngle, leftAngle);
    // 左右の進行距離
    leftDifference = std::abs(leftActual - leftInitial);
    rightDifference = std::abs(rightActual - rightInitial);
    // 走行距離のテスト
    EXPECT_LE(expectedDistance, currentDistance);
    EXPECT_GE(expectedDistance + distanceError, currentDistance);
    // 直進できているかのテスト
    EXPECT_GE(differenceError, std::abs(leftDifference - rightDifference));
  }

  TEST(runStraightToDistanceTest, runStraightToDistanceZero)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, currentDistance;

    double targetDistance = 0;
    int pwm = 100;

    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount())
                       + targetDistance;
    // 直進
    straightRunner.runStraightToDistance(targetDistance, pwm);
    // 関数実行後の走行距離
    currentDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 走行距離のテスト
    EXPECT_EQ(expectedDistance, currentDistance);
  }

  TEST(runStraightToDistanceTest, runStraightToDistanceMinusPwm)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, currentDistance;
    double leftAngle, rightAngle;
    double leftInitial, rightInitial;
    double leftActual, rightActual;
    double leftDifference, rightDifference;

    double targetDistance = 350;
    int pwm = -50;
    double distanceError = 3.0, differenceError = 1.0;

    // 初期値
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftInitial = Mileage::calculateWheelMileage(leftAngle);
    rightInitial = Mileage::calculateWheelMileage(rightAngle);
    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(rightAngle, leftAngle) - targetDistance;
    // 直進
    straightRunner.runStraightToDistance(targetDistance, pwm);
    // 関数実行後の走行距離
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftActual = Mileage::calculateWheelMileage(leftAngle);
    rightActual = Mileage::calculateWheelMileage(rightAngle);
    currentDistance = Mileage::calculateMileage(rightAngle, leftAngle);
    // 左右の進行距離
    leftDifference = std::abs(leftActual - leftInitial);
    rightDifference = std::abs(rightActual - rightInitial);
    // 走行距離のテスト
    EXPECT_GE(expectedDistance, currentDistance);
    EXPECT_LE(expectedDistance - distanceError, currentDistance);
    // 直進できているかのテスト
    EXPECT_GE(differenceError, std::abs(leftDifference - rightDifference));
  }

  TEST(runStraightToDistanceTest, runStraightToDistanceMinusFullPwm)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, currentDistance;
    double leftAngle, rightAngle;
    double leftInitial, rightInitial;
    double leftActual, rightActual;
    double leftDifference, rightDifference;

    double targetDistance = 350;
    int pwm = -100;
    double distanceError = 3.5, differenceError = 1.0;

    // 初期値
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftInitial = Mileage::calculateWheelMileage(leftAngle);
    rightInitial = Mileage::calculateWheelMileage(rightAngle);
    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(rightAngle, leftAngle) - targetDistance;
    // 直進
    straightRunner.runStraightToDistance(targetDistance, pwm);
    // 関数実行後の走行距離
    leftAngle = measurer.getLeftCount();
    rightAngle = measurer.getRightCount();
    leftActual = Mileage::calculateWheelMileage(leftAngle);
    rightActual = Mileage::calculateWheelMileage(rightAngle);
    currentDistance = Mileage::calculateMileage(rightAngle, leftAngle);
    // 左右の進行距離
    leftDifference = std::abs(leftActual - leftInitial);
    rightDifference = std::abs(rightActual - rightInitial);
    // 走行距離のテスト
    EXPECT_GE(expectedDistance, currentDistance);
    EXPECT_LE(expectedDistance - distanceError, currentDistance);
    // 直進できているかのテスト
    EXPECT_GE(differenceError, std::abs(leftDifference - rightDifference));
  }

  TEST(runStraightToDistanceTest, runStraightToDistancePwmZero)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, currentDistance;

    double targetDistance = 350;
    int pwm = 0;

    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 直進
    straightRunner.runStraightToDistance(targetDistance, pwm);
    // 関数実行後の走行距離
    currentDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 走行距離のテスト
    EXPECT_EQ(expectedDistance, currentDistance);
  }

  TEST(runStraightToDistanceTest, runStraightToMinusDistancePwmZero)
  {
    Measurer measurer;
    StraightRunner straightRunner;
    double expectedDistance, currentDistance;

    double targetDistance = -350;
    int pwm = 0;

    // 期待する走行距離
    expectedDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 直進
    straightRunner.runStraightToDistance(targetDistance, pwm);
    // 関数実行後の走行距離
    currentDistance = Mileage::calculateMileage(measurer.getRightCount(), measurer.getLeftCount());
    // 走行距離のテスト
    EXPECT_EQ(expectedDistance, currentDistance);
  }
}  // namespace etrobocon2022_test