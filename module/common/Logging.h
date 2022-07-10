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
   * 入力された文字列をLogとしてターミナルに表示
   * @param logMessage 表示するLogメッセージ
   */
  void writeLogMessage(const char* logMessage);

  /**
   * 入力された文字列をwarningMessageとして色を変更し、ターミナルに表示
   * @param warningMessage 表示するwarningメッセージ
   */
  void writeWarningMessage(const char* warningMessage);

  /**
   * 入力された文字列をerrorMessageとして色を変更し、ターミナルに表示
   * @param errorMessage 表示するerrorメッセージ
   */
  void writeErrorMessage(const char* errorMessage);

  /**
   * 入力された文字列をhighlightLogとして色を変更し、ターミナルに表示
   * @param hilightLog 表示するhighlightlogメッセージ
   */
  void writeHighlightLog(const char* highlightLog);

 private:
  char* Logs;  // システムのログを保持する
};

#endif