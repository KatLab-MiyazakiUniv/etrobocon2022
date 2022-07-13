/**
 * @file Logger.h
 * @brief 動作確認に用いるprintf()関数を所持するクラス
 * @author sap2368
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

class Logger {
 public:
  Logger();

  /**
   * 入力された文字列をLogとしてターミナルに表示
   * @param logMessage 表示するLogメッセージ
   */
  void log(const char* logMessage);

  /**
   * 入力された文字列をwarningMessageとして色を変更し、ターミナルに表示
   * @param warningMessage 表示するwarningメッセージ
   */
  void logWarning(const char* warningMessage);

  /**
   * 入力された文字列をerrorMessageとして色を変更し、ターミナルに表示
   * @param errorMessage 表示するerrorメッセージ
   */
  void logError(const char* errorMessage);

  /**
   * 入力された文字列をhighlightLogとして色を変更し、ターミナルに表示
   * @param hilightLog 表示するhighlightlogメッセージ
   */
  void logHighlight(const char* highlightLog);

 private:
  char* Logs;  // システムのログを保持する
};

#endif