/**
 * @file   MotionParserTest.cpp
 * @brief  MotionParserクラスをテストする
 * @author mutotaka0426
 */

#include "MotionParser.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace std;

namespace etrobocon2022_test {
  TEST(MotionParserTest, createMotions)
  {
    constexpr char* filePath = "../test/test_data/CommandParserTestData.csv";
    int targetBrightness = 45;
    bool isLeftEdge = true;
    // actualListの生成とlogRunning()のログを取る
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    std::vector<Motion*> actualList
        = MotionParser::createMotions(filePath, targetBrightness, isLeftEdge);

    for(const auto a : actualList) {
      a->logRunning();
    }
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    /**
     * test_data/CommandParserTestData.csvに従って
     * 順にインスタンス化したものをexpectedListに追加する
     */
    std::vector<Motion*> expectedList;
    DistanceLineTracing* dl = new DistanceLineTracing(1080, targetBrightness + 10, 70,
                                                      PidGain(0.2, 0.8, 0.1), isLeftEdge);
    expectedList.push_back(dl);
    ColorLineTracing* cl = new ColorLineTracing(COLOR::RED, targetBrightness + 0, 30,
                                                PidGain(0.1, 0.2, 0.3), isLeftEdge);
    expectedList.push_back(cl);
    DistanceStraight* ds = new DistanceStraight(100.2, 100);
    expectedList.push_back(ds);
    ColorStraight* cs = new ColorStraight(COLOR::GREEN, 100);
    expectedList.push_back(cs);
    Rotation* rt = new Rotation(90, 80, false);
    expectedList.push_back(rt);
    DistanceTurning* dt = new DistanceTurning(350, 50, 60);
    expectedList.push_back(dt);
    EdgeChanging* ec = new EdgeChanging(isLeftEdge, false);
    expectedList.push_back(ec);
    Sleeping* sl = new Sleeping(1000);
    expectedList.push_back(sl);
    ArmRising* ar = new ArmRising(10, 100);
    expectedList.push_back(ar);

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: ../test/test_data/CommandParserTestData.csv:10: ";
    expectedOutput += "'UNDEFINED' is undefined command";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    // expectedListのログを取る
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    for(const auto e : expectedList) {
      e->logRunning();
    }
    expectedOutput += testing::internal::GetCapturedStdout();  // キャプチャ終了

    EXPECT_EQ(expectedOutput, actualOutput);  // ログが一致していることを確認する
  }

  TEST(MotionParserTest, notCreateMotions)
  {
    constexpr char* filePath = "../test/test_data/non_existent_file.csv";  // 存在しないファイル
    int targetBrightness = 45;
    bool isLeftEdge = false;
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    std::vector<Motion*> actualList
        = MotionParser::createMotions(filePath, targetBrightness, isLeftEdge);
    string actualOutput = testing::internal::GetCapturedStdout();  // キャプチャ終了

    std::vector<Motion*> expectedList;

    // Warning文
    string expectedOutput = "\x1b[36m";  // 文字色をシアンに
    expectedOutput += "Warning: ../test/test_data/non_existent_file.csv file not open!\n";
    expectedOutput += "\n\x1b[39m";  // 文字色をデフォルトに戻す

    EXPECT_EQ(expectedOutput, actualOutput);  // 標準出力でWarningを出している
    EXPECT_EQ(expectedList, actualList);  // ファイルを読み込めないためリストは空のまま
  }

}  // namespace etrobocon2022_test
