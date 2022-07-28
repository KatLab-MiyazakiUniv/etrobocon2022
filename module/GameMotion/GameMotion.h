/**
 * @file GameMotion.h
 * @brief ゲーム動作の親クラス
 * @author kodama0720
 */

#ifndef GAME_MOTION_H
#define GAME_MOTION_H

#include "LineTracer.h"
#include "Rotation.h"
#include "StraightRunner.h"

class GameMotion {
 public:
  /**
   * コンストラクタ
   */
  GameMotion(bool& isLeftEdge, double time, double risk);

  /**
   * @brief ゲームエリア走行の純粋仮想関数（抽象メソッド）
   */
  virtual void run(bool& isLeftEdge) = 0;

  /**
   * @brief 動作時間を取得する
   * @return 動作時間
   */
  double getMotionTime(void);

  /**
   * @brief 失敗リスクを取得する
   * @return 失敗リスク
   */
  double getFailureRisk(void);

 private:
  const double MOTION_TIME;
  const double FAILURE_RISK;

 protected:
  LineTracer lineTracer;
  Rotation rotation;
  StraightRunner straightRunner;
};

#endif
