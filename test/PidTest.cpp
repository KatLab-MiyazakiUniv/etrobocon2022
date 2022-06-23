/**
 * @file PidTest.cpp
 * @brief PidGainクラス,Pidクラスをテストする
 * @author kawano
 */

#include "Pid.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {
  TEST(PidGainTest, gain)
  {
    double expected_p = 0.1;
    double expected_i = 0.03;
    double expected_d = 0.612;
    PidGain actualPidGain(expected_p, expected_i, expected_d);
    EXPECT_DOUBLE_EQ(expected_p, actualPidGain.kp);
    EXPECT_DOUBLE_EQ(expected_i, actualPidGain.ki);
    EXPECT_DOUBLE_EQ(expected_d, actualPidGain.kd);
  }

  TEST(PidGainTest, gainZero)
  {
    double expected_p = 0.0;
    double expected_i = 0.0;
    double expected_d = 0.0;
    PidGain actualPidGain(expected_p, expected_i, expected_d);
    EXPECT_DOUBLE_EQ(expected_p, actualPidGain.kp);
    EXPECT_DOUBLE_EQ(expected_i, actualPidGain.ki);
    EXPECT_DOUBLE_EQ(expected_d, actualPidGain.kd);
  }

  TEST(PidGainTest, gainMinus)
  {
    double expected_p = -0.5;
    double expected_i = -0.2;
    double expected_d = -0.3;
    PidGain actualPidGain(expected_p, expected_i, expected_d);
    EXPECT_DOUBLE_EQ(expected_p, actualPidGain.kp);
    EXPECT_DOUBLE_EQ(expected_i, actualPidGain.ki);
    EXPECT_DOUBLE_EQ(expected_d, actualPidGain.kd);
  }

  TEST(PidTest, calculatePid)
  {
    constexpr double DELTA = 0.01;
    double expected_p = 0.6;
    double expected_i = 0.02;
    double expected_d = 0.03;
    double targetValue = 70;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double currentValue = 20;
    double preDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * expected_p;
    double i = currentDeviation * DELTA * expected_i;
    double d = (currentDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
  }

  TEST(PidTest, calculatePidZero)
  {
    constexpr double DELTA = 0.01;
    double expected_p = 0.0;
    double expected_i = 0.0;
    double expected_d = 0.0;
    double targetValue = 0;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double currentValue = 40;
    double preDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * expected_p;
    double i = currentDeviation * DELTA * expected_i;
    double d = (currentDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
  }

  TEST(calculatePidTest, calculatePidMinus)
  {
    constexpr double DELTA = 0.01;
    double expected_p = -0.3;
    double expected_i = -0.02;
    double expected_d = -0.175;
    double targetValue = 100;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double currentValue = 0;
    double preDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * expected_p;
    double i = currentDeviation * DELTA * expected_i;
    double d = (currentDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
  }

  TEST(PidTest, calculatePidChangeDelta)
  {
    constexpr double DELTA = 0.03;
    double expected_p = 0.6;
    double expected_i = 0.02;
    double expected_d = 0.03;
    double targetValue = 70;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double currentValue = 55;
    double preDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * expected_p;
    double i = currentDeviation * DELTA * expected_i;
    double d = (currentDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    //第2引数に周期を渡し、周期に応じた計算結果を返すことができるかを確認(デフォルトでは0.01が渡される)
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue, DELTA));
  }

  TEST(PidTest, calculatePidChangeDeltaMinus)
  {
    constexpr double DELTA = -0.03;
    double expected_p = 0.6;
    double expected_i = 0.02;
    double expected_d = 0.03;
    double targetValue = 70;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double currentValue = 55;
    double preDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * expected_p;
    double i = currentDeviation * DELTA * expected_i;
    double d = (currentDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    //第2引数に周期を渡し、周期に応じた計算結果を返すことができるかを確認(デフォルトでは0.01が渡される)
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue, DELTA));
  }

  //周期に0を渡したときに、デフォルト周期0.01として計算されるかをテストする
  TEST(PidTest, calculatePidChangeDeltaZero)
  {
    constexpr double DELTA = 0;              //実際に渡す周期
    constexpr double EXPECTED_DELTA = 0.01;  //期待される周期
    double expected_p = 0.6;
    double expected_i = 0.02;
    double expected_d = 0.03;
    double targetValue = 70;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double currentValue = 55;
    double preDeviation = 0;
    double currentDeviation = (targetValue - currentValue);
    double p = currentDeviation * expected_p;
    double i = currentDeviation * EXPECTED_DELTA * expected_i;
    double d = (currentDeviation - preDeviation) * expected_d / EXPECTED_DELTA;
    double expected = p + i + d;
    //第2引数に周期を渡し、周期に応じた計算結果を返すことができるかを確認(デフォルトでは0.01が渡される)
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue, DELTA));
  }

  // setしてcalculatePidを呼び出す(Setterのテスト)
  TEST(calculatePidTest, caluclatePidSetter)
  {
    constexpr double DELTA = 0.01;
    double expected_p = 0.6;
    double expected_i = 0.05;
    double expected_d = 0.01;
    double targetValue = 70;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double currentValue = 60;
    double preDeviation = 0;
    double currentDiviation = (targetValue - currentValue);  //現在の偏差
    double p = currentDiviation * expected_p;                // P制御
    double i = currentDiviation * DELTA * expected_i;        // I制御(誤差の累積は0)
    double d = (currentDiviation - preDeviation) * expected_d / DELTA;  // D制御(前回の誤差は0)
    double expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));

    double integral = currentDiviation * DELTA;  //誤差の累積
    preDeviation += currentDiviation;            //前回の誤差の更新
    expected_p = 0.1;
    expected_i = 0.2;
    expected_d = 0.3;
    actualPid.setPidGain(expected_p, expected_i, expected_d);  // PIDゲインの更新
    currentValue = 100;
    currentDiviation = (targetValue - currentValue);
    integral += currentDiviation * DELTA;
    p = currentDiviation * expected_p;
    i = integral * expected_i;
    d = (currentDiviation - preDeviation) / DELTA * expected_d;
    expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(currentValue));
  }

}  // namespace etrobocon2022_test
