/**
 * @file Logger.h
 * @brief 動作確認に用いるprintf()関数を所持するクラス
 * @author sap2368 mutotaka0426
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Logger {
 public:
  Logger();

  /**
   * @brief 入力された文字列をLogとしてターミナルに表示
   * @param logMessage 表示するLogメッセージ
   */
  void log(const char* logMessage);

  /**
   * @brief 入力された文字列をwarningMessageとして色を変更し、ターミナルに表示
   * @param warningMessage 表示するwarningメッセージ
   */
  void logWarning(const char* warningMessage);

  /**
   * @brief 入力された文字列をerrorMessageとして色を変更し、ターミナルに表示
   * @param errorMessage 表示するerrorメッセージ
   */
  void logError(const char* errorMessage);

  /**
   * @brief 入力された文字列をhighlightLogとして色を変更し、ターミナルに表示
   * @param hilightLog 表示するhighlightlogメッセージ
   */
  void logHighlight(const char* highlightLog);

  /**
   * @brief 記録したログをファイル出力する
   */
  void outputToFile();

  /**
   * @brief 記録したログを初期化する
   */
  void initLogs();

 private:
  static char logs[65536];  // システムのログを保持する領域
};

#endif
