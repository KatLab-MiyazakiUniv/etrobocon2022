/**
 * @file LoggerTest.cpp
 * @brief Loggerクラスをテストする
 * @author sap268 mutotaka0426
 */

#include "Logger.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <err.h>

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

  TEST(LoggerTest, outputToFile)
  {
    // 異なるLoggerインスタンスを用いてログを取る
    Logger logger1;
    Logger logger2;
    logger1.initLogs();  // logsを初期化
    // 各ログ出力の関数を実行する
    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    logger1.log("log text");
    logger2.logWarning("log warning-text");
    logger1.logError("log error-text");
    logger2.logHighlight("log highlight-text");
    std::string _ = testing::internal::GetCapturedStdout();  // キャプチャ終了
    // 期待出力をセットする
    std::string expected = "log text\n";
    expected += "log warning-text\n";
    expected += "log error-text\n";
    expected += "log highlight-text\n";

    logger1.outputToFile();  // ログファイルを生成

    const int BUF_SIZE = 64;
    char filePath[BUF_SIZE] = "./etrobocon2022/logfiles/";
    char fileName[BUF_SIZE];  // outputToFile()で作成したログファイル
    const char* cmdline = "ls -rt ./etrobocon2022/logfiles | tail -n 1";
    FILE* fp = popen(cmdline, "r");  // 上記コマンドにより最新のログファイルを取得する
    // コマンドの実行結果を取得出来ない場合エラーを出す
    if((fp = popen(cmdline, "r")) == NULL) {
      err(EXIT_FAILURE, "%s", cmdline);
    }
    fgets(fileName, BUF_SIZE, fp);  // コマンドの実行結果をfileNameにセット
    pclose(fp);
    char* endPoint = strchr(fileName, '\n');        // 改行があるポインタを取得
    if(endPoint != NULL) *endPoint = '\0';          // 改行を削除
    strncat(filePath, fileName, sizeof(filePath));  // filePathとfileNameを結合する

    const int LINE_SIZE = 256;
    char line[LINE_SIZE];
    FILE* file = fopen(filePath, "r");
    // 直前に生成したログファイルの文字列をセットする
    std::string actual = "";
    while(fgets(line, LINE_SIZE, file) != NULL) {
      actual += line;
    }
    fclose(file);

    ASSERT_STREQ(expected.c_str(), actual.c_str());  // ログファイルの中身をテスト
  }

}  // namespace etrobocon2022_test
