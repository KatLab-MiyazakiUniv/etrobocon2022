/**
 * @file LoggerTest.cpp
 * @brief Loggerクラスをテストする
 * @author sap268
 */

#include "Logger.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

namespace etrobocon2022_test {
  TEST(LoggerTest, log)
  {
    Logger logger;
    std::string logMsg = "logs test.";
    std::string expected = logMsg + "\n";
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    logger.log(logMsg.c_str());
    std::string actual = testing::internal::GetCapturedStdout();  // キャプチャ終了
    ASSERT_STREQ(expected.c_str(), actual.c_str());
  }

  TEST(LoggerTest, logWarning)
  {
    Logger logger;
    std::string logMsg = "WarningMessage test.";
    std::string expected = "\x1b[36m";  // 文字色をシアンに
    expected += "Warning: " + logMsg + "\n";
    expected += "\x1b[39m";              // 文字色をデフォルトに戻す
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    logger.logWarning(logMsg.c_str());
    std::string actual = testing::internal::GetCapturedStdout();  // キャプチャ終了
    ASSERT_STREQ(expected.c_str(), actual.c_str());
  }

  TEST(LoggerTest, logError)
  {
    Logger logger;
    std::string logMsg = "ErrorMessage test.";
    std::string expected = "\x1b[35m";  // 文字色をマゼンタに
    expected += "Error: " + logMsg + "\n";
    expected += "\x1b[39m";              // 文字色をデフォルトに戻す
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    logger.logError(logMsg.c_str());
    std::string actual = testing::internal::GetCapturedStdout();  // キャプチャ終了
    ASSERT_STREQ(expected.c_str(), actual.c_str());
  }

  TEST(LoggerTest, logHighlight)
  {
    Logger logger;
    std::string logMsg = "HighlightLog test.";
    std::string expected = "\x1b[32m";  // 文字色を緑色に
    expected += logMsg + "\n";
    expected += "\x1b[39m";              // 文字色をデフォルトに戻す
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    logger.logHighlight(logMsg.c_str());
    std::string actual = testing::internal::GetCapturedStdout();  // キャプチャ終了
    ASSERT_STREQ(expected.c_str(), actual.c_str());
  }

}  // namespace etrobocon2022_test
