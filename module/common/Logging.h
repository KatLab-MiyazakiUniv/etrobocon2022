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

  //入力された文字列をLogとしてターミナルに表示
  void writeLogs(const char* logs);
  //入力された文字列を色を変更してwarningMessageとしてターミナルに表示
  void writeWarningMessage(const char* warningMessage);
  //入力された文字列を色を変更してerrorMessageとしてターミナルに表示
  void writeErrorMessage(const char* errorMessage);

 private:
  char* Logs;
};

#endif