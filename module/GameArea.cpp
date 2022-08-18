/**
 * @file   GameArea.cpp
 * @brief  ゲームエリアを攻略するクラス
 * @author kawanoichi kodama0720 mutotaka0426
 */

#include "GameArea.h"

using namespace std;

void GameArea::runGameArea(const bool isLeftCourse, bool& isLeftEdge, const int targetBrightness)
{
  const int BUF_SIZE = 128;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域
  Logger logger;

  // ファイルから受け取る動作リスト
  vector<Motion*> toEndPointMotions;  // 端点サークルまでの動作リスト
  vector<Motion*> gameAreaMotions;    // ゲームエリア攻略の動作リスト

  // 端点サークルまでのコマンドファイルを読み込む
  const char* toEndPointPath = isLeftCourse ? toEndPointLeft : toEndPointRight;
  // 端点サークルまでの動作インスタンスのリストを生成する
  toEndPointMotions = MotionParser::createMotions(toEndPointPath, targetBrightness, isLeftEdge);

  // 動作実行のメッセージログを出す
  snprintf(buf, BUF_SIZE, "\nRun the commands in '%s'\n", toEndPointPath);
  logger.logHighlight(buf);
  // 各動作を実行する
  for(const auto& eMotion : toEndPointMotions) {
    eMotion->logRunning();
    eMotion->run();
  }

  // ゲームエリア攻略のコマンドファイルを読み込む
  const char* gameAreaPath = isLeftCourse ? gameAreaLeft : gameAreaRight;
  // ゲームエリア攻略の動作インスタンスのリストを生成する
  gameAreaMotions = MotionParser::createMotions(gameAreaPath, targetBrightness, isLeftEdge);

  // 動作実行のメッセージログを出す
  snprintf(buf, BUF_SIZE, "\nRun the commands in '%s'\n", gameAreaPath);
  logger.logHighlight(buf);
  // 各動作を実行する
  for(const auto& gMotion : gameAreaMotions) {
    gMotion->logRunning();
    gMotion->run();
  }
}
