/**
 * @file Logger.cpp
 * @brief 動作確認に用いるprintf()関数を所持するクラス
 * @author sap2368 mutotaka0426
 */
#include "Logger.h"

Logger::Logger() {}

void Logger::log(const char* logMessage)
{
  const int BUF_SIZE = 128;
  char message[BUF_SIZE];  // 表示するメッセージ
  snprintf(message, BUF_SIZE, "%s\n", logMessage);
  printf("%s", message);

  strncat(logs, message, sizeof(logs));  // logsとmessageを結合する
}

void Logger::logWarning(const char* warningMessage)
{
  const int BUF_SIZE = 128;
  char message[BUF_SIZE];  // 表示するメッセージ
  snprintf(message, BUF_SIZE, "%s\n", warningMessage);
  printf("\x1b[36m"); /* 文字色をシアンに */
  printf("Warning: %s", message);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */

  strncat(logs, message, sizeof(logs));  // logsとmessageを結合する
}

void Logger::logError(const char* errorMessage)
{
  const int BUF_SIZE = 128;
  char message[BUF_SIZE];  // 表示するメッセージ
  snprintf(message, BUF_SIZE, "%s\n", errorMessage);
  printf("\x1b[35m"); /* 文字色をマゼンタに */
  printf("Error: %s", message);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */

  strncat(logs, message, sizeof(logs));  // logsとmessageを結合する
}

void Logger::logHighlight(const char* highlightLog)
{
  const int BUF_SIZE = 128;
  char message[BUF_SIZE];  // 表示するメッセージ
  snprintf(message, BUF_SIZE, "%s\n", highlightLog);
  printf("\x1b[32m"); /* 文字色を緑色に */
  printf("%s", message);
  printf("\x1b[39m"); /* 文字色をデフォルトに戻す */

  strncat(logs, message, sizeof(logs));  // logsとmessageを結合する
}

void Logger::outputToFile()
{
  FILE* outputFile;
  const char* fileName = "logfile.txt";  // 暫定のファイル名
  outputFile = fopen(fileName, "w");     // logfile.txtを作成
  if(outputFile == NULL) {
    logWarning("cannot open file");
    return;
  }
  fprintf(outputFile, logs);  // logsの内容をlogfile.txtに書き込む
  fclose(outputFile);

  /*
  NOTE: ロボコン環境だと，時刻を取得するtime.hのtime()や，
  ディレクトリを生成するためのヘッダdirect.hを使用できないため（多分），
  bashでlogfile.txtの名前をログ生成時刻に変更し，logfiles/に移動する
  */
  system("bash ./etrobocon2022/scripts/organizeLogfile.sh &");
}

void Logger::initLogs()
{
  logs[0] = '\0';  // 文字列を初期化
}

char Logger::logs[65536] = "";  // logsを初期化
