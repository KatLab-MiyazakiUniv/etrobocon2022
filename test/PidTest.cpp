/**
 * @file PidTest.cpp
 * @brief PidGainクラス,Pidクラスをテストする
 * @author kawano
 */

#include "Pid.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test
{
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
    double nowValue = 20;
    double preDeviation = 0;
    double nowDeviation = (targetValue - nowValue);
    double p = nowDeviation * expected_p;
    double i = nowDeviation * DELTA * expected_i;
    double d = (nowDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(nowValue));
  }

  TEST(PidTest, calculatePidZero)
  {
    static const double DELTA = 0.01;
    double expected_p = 0.0;
    double expected_i = 0.0;
    double expected_d = 0.0;
    double targetValue = 0;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double nowValue = 40;
    double preDeviation = 0;
    double nowDeviation = (targetValue - nowValue);
    double p = nowDeviation * expected_p;
    double i = nowDeviation * DELTA * expected_i;
    double d = (nowDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(nowValue));
  }

  TEST(calculatePidTest, calculatePidMinus)
  {
    static const double DELTA = 0.01;
    double expected_p = -0.3;
    double expected_i = -0.02;
    double expected_d = -0.175;
    double targetValue = 100;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double nowValue = 0;
    double preDeviation = 0;
    double nowDeviation = (targetValue - nowValue);
    double p = nowDeviation * expected_p;
    double i = nowDeviation * DELTA * expected_i;
    double d = (nowDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(nowValue));
  }

  TEST(PidTest, calculatePidChangeDelta)
  {
    static const double DELTA = 0.03;
    double expected_p = 0.6;
    double expected_i = 0.02;
    double expected_d = 0.03;
    double targetValue = 70;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double nowValue = 55;
    double preDeviation = 0;
    double nowDeviation = (targetValue - nowValue);
    double p = nowDeviation * expected_p;
    double i = nowDeviation * DELTA * expected_i;
    double d = (nowDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    //第2引数に周期を渡し、周期に応じた計算結果を返すことができるかを確認(デフォルトでは0.01が渡される)
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(nowValue, DELTA));
  }

  TEST(PidTest, calculatePidChangeDeltaMinus)
  {
    static const double DELTA = -0.03;
    double expected_p = 0.6;
    double expected_i = 0.02;
    double expected_d = 0.03;
    double targetValue = 70;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double nowValue = 55;
    double preDeviation = 0;
    double nowDeviation = (targetValue - nowValue);
    double p = nowDeviation * expected_p;
    double i = nowDeviation * DELTA * expected_i;
    double d = (nowDeviation - preDeviation) * expected_d / DELTA;
    double expected = p + i + d;
    //第2引数に周期を渡し、周期に応じた計算結果を返すことができるかを確認(デフォルトでは0.01が渡される)
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(nowValue, DELTA));
  }

  //周期に0を渡したときに、デフォルト周期0.01として計算されるかをテストする
  TEST(PidTest, calculatePidChangeDeltaZero)
  {
    static const double DELTA = 0;             //実際に渡す周期
    static const double EXPECTED_DELTA = 0.01; //期待される周期
    double expected_p = 0.6;
    double expected_i = 0.02;
    double expected_d = 0.03;
    double targetValue = 70;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double nowValue = 55;
    double preDeviation = 0;
    double nowDeviation = (targetValue - nowValue);
    double p = nowDeviation * expected_p;
    double i = nowDeviation * EXPECTED_DELTA * expected_i;
    double d = (nowDeviation - preDeviation) * expected_d / EXPECTED_DELTA;
    double expected = p + i + d;
    //第2引数に周期を渡し、周期に応じた計算結果を返すことができるかを確認(デフォルトでは0.01が渡される)
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(nowValue, DELTA));
  }

  // setしてcalculatePidを呼び出す(Setterのテスト)
  TEST(calculatePidTest, caluclatePidSetter)
  {
    static const double DELTA = 0.01;
    double expected_p = 0.6;
    double expected_i = 0.05;
    double expected_d = 0.01;
    double targetValue = 70;
    Pid actualPid(expected_p, expected_i, expected_d, targetValue);
    double nowValue = 60;
    double preDeviation = 0;
    double nowDiviation = (targetValue - nowValue);                //現在の偏差
    double p = nowDiviation * expected_p;                          // P制御
    double i = nowDiviation * DELTA * expected_i;                  // I制御(誤差の累積は0)
    double d = (nowDiviation - preDeviation) * expected_d / DELTA; // D制御(前回の誤差は0)
    double expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(nowValue));

    double integral = nowDiviation * DELTA; //誤差の累積
    preDeviation += nowDiviation;           //前回の誤差の更新
    expected_p = 0.1;
    expected_i = 0.2;
    expected_d = 0.3;
    actualPid.setPidGain(expected_p, expected_i, expected_d); // PIDゲインの更新
    nowValue = 100;
    nowDiviation = (targetValue - nowValue);
    integral += nowDiviation * DELTA;
    p = nowDiviation * expected_p;
    i = integral * expected_i;
    d = (nowDiviation - preDeviation) / DELTA * expected_d;
    expected = p + i + d;
    EXPECT_DOUBLE_EQ(expected, actualPid.calculatePid(nowValue));
  }

} // namespace etrobocon2022_test
