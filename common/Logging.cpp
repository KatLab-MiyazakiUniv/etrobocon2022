/**
 * @file Logging.h
 * @brief 動作確認に用いるprintf()関数を所持するクラス
 * @author sap2368
 */
#include "Logging.h"

Logging::Logging() {}

void Logging::writeLogs(const char* logs)
{
  const char* log = logs;
  printf("\x1b[36m"); /* 文字色をシアンに */
  printf("Logs: %s\n", log);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
}

void Logging::writeWarnings(const char* warnings)
{
  const char* warning = warnings;
  printf("\x1b[33m"); /* 文字色を黄色に */
  printf("Warnings: %s\n", warning);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
}

void Logging::writeErrors(const char* errors)
{
  const char* error = errors;
  printf("\x1b[35m"); /* 文字色をマゼンタに */
  printf("Errors: %s\n", error);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */
}