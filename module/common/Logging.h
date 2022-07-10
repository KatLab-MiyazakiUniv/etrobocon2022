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

  /**
  ** 入力された文字列をLogとしてターミナルに表示
  ** @param logMessage
  **/
  void writeLogMessage(const char* logMessage);

  /**
  ** 入力された文字列をwarningMessageとして色を変更し、ターミナルに表示
  ** @param warningMessage
  **/
  void writeWarningMessage(const char* warningMessage);

  /**
  ** 入力された文字列をerrorMessageとして色を変更し、ターミナルに表示
  ** @param errorMessage
  **/
  void writeErrorMessage(const char* errorMessage);

  /**
  ** 入力された文字列をhighlightLogとして色を変更し、ターミナルに表示
  ** @param hilightLog
  **/
  void writeHighlightLog(const char* highlightLog);

 private:
  char* Logs;  // システムのログを保持する
};

#endif