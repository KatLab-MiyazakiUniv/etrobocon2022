/**
 * @file Logging.cpp
 * @brief 動作確認に用いるprintf()関数を所持するクラス
 * @author sap2368
 */
#include "Logging.h"

Logging::Logging() {}

void Logging::writeLogs(const char* logs)
{
  const char* log = logs;
  printf("%s\n", log);
}

void Logging::writeWarningMessage(const char* warningMessage)
{
  const char* warning = warningMessage;
  printf("\x1b[36m"); /* 文字色をシアンに */
  printf("Warning: %s\n", warning);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
}

void Logging::writeErrorMessage(const char* errorMessage)
{
  const char* error = errorMessage;
  printf("\x1b[35m"); /* 文字色をマゼンタに */
  printf("Error: %s\n", error);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
}