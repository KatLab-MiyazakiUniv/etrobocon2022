/**
 * @file Logging.h
 * @brief 動作確認に用いるprintf()関数を所持するクラス
 * @author sap2368
 */
#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

class Logging {
 public:
  Logging();

  void writeLogs(const char* logs);

  void writeWarnings(const char* warnings);

  void writeErrors(const char* errors);
};

#endif