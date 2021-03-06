/**
 * @file Logger.cpp
 * @brief 動作確認に用いるprintf()関数を所持するクラス
 * @author sap2368
 */
#include "Logger.h"

Logger::Logger() {}

void Logger::log(const char* logMessage)
{
  const char* log = logMessage;
  printf("%s\n", log);
}

void Logger::logWarning(const char* warningMessage)
{
  const char* warning = warningMessage;
  printf("\x1b[36m"); /* 文字色をシアンに */
  printf("Warning: %s\n", warning);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
}

void Logger::logError(const char* errorMessage)
{
  const char* error = errorMessage;
  printf("\x1b[35m"); /* 文字色をマゼンタに */
  printf("Error: %s\n", error);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
}

void Logger::logHighlight(const char* highlightLog)
{
  const char* hlog = highlightLog;
  printf("\x1b[32m"); /* 文字色を緑色に */
  printf("%s\n", hlog);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
}
