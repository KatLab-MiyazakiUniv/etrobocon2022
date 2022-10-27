/**
 * @file CalibratorTest.cpp
 * @brief Calibratorクラスのテスト
 * @author mutotaka0426
 */

#include "Calibrator.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <time.h>

using namespace std;

namespace etrobocon2022_test {

  TEST(CalibratorTest, run)
  {
    Calibrator calibrator;
    srand(2);  // SPIKEの電圧が標準値でLeftコースを選択する乱数シード
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    calibrator.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("Will Run on the Left Course") != string::npos
                  && output.find("Warning") == string::npos  // Warningがない
                  && output.find("Error") == string::npos;   // Errorがない

    EXPECT_TRUE(actual);  // 期待した出力がされており，WarningやErrorが出ていないかテスト
  }

  // 電圧のWarningが出るテスト
  TEST(CalibratorTest, runVoltageWorning)
  {
    Calibrator calibrator;
    srand(0);  // SPIKEの電圧が4196でRightコースを選択する乱数シード
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    calibrator.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual
        = output.find("Will Run on the Right Course") != string::npos
          && output.find("Warning: Voltage is low\n") != string::npos  // 電圧のWarningが出ている
          && output.find("Error") == string::npos;                     // Errorがない

    EXPECT_TRUE(actual);  // 電圧のWarningが出てErrorが出ていないかテスト
  }

  TEST(CalibratorTest, waitForStart)
  {
    Calibrator calibrator;
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    calibrator.waitForStart();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // find("str")はstrが見つからない場合string::nposを返す
    bool actual = output.find("On standby.\n\nSignal within 5cm from Sonar Sensor.") != string::npos
                  && output.find("Warning") == string::npos  // Warningがない
                  && output.find("Error") == string::npos;   // Errorがない

    EXPECT_TRUE(actual);  // 期待した出力がされており，WarningやErrorが出ていないかテスト
  }

  TEST(CalibratorTest, getIsLeftCourse)
  {
    Calibrator calibrator;
    srand((unsigned int)time(NULL));     //現在時刻を元に乱数シードを生成
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    calibrator.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了
    bool expected;

    // Leftコースと出力されていた場合
    if(output.find("Will Run on the Left Course") != string::npos) {
      expected = true;  // Lコース
    }
    // Rightコースト出力されていた場合
    else if(output.find("Will Run on the Right Course") != string::npos) {
      expected = false;  // Rコース
    }
    // 想定していない状況
    else {
      expected = NULL;
    }

    bool actual = calibrator.getIsLeftCourse();  // 実際のisLeftCourseを取得

    EXPECT_EQ(expected, actual);  // 出力とゲッタの値が等しいかテスト
  }

  TEST(CalibratorTest, getTargetBrightness)
  {
    Calibrator calibrator;
    srand((unsigned int)time(NULL));     //現在時刻を元に乱数シードを生成
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    calibrator.run();
    string output = testing::internal::GetCapturedStdout();  // キャプチャ終了

    string targetString = "Target Brightness is ";  // 目標輝度値の直前に書かれている文字列

    // 出力された目標輝度値を取得
    int index = output.find(targetString) + targetString.length();
    string expectedStr = output.substr(index);  // 輝度値を取得（文字列）
    int expected = stoi(expectedStr);           // 文字列を整数値に変換

    int actual = calibrator.getTargetBrightness();  // 実際の輝度値を取得

    EXPECT_EQ(expected, actual);  // 出力とゲッタの値が等しいかテスト
  }
}  // namespace etrobocon2022_test
