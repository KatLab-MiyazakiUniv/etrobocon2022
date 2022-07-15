/**
 * @file BingoMotion.h
 * @brief ビンゴ動作の親クラス
 * @author kodama0720
 */

#ifndef BINGO_MOTION_H
#define BINGO_MOTION_H

class GameMotion {
 public:
  /**
   * コンストラクタ
   */
  GameMotion(double time = 0, double risk = 0);

  /**
   * ゲームエリア走行の純粋仮想関数（抽象メソッド）
   */
  virtual void run() = 0;

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
  double MOTION_TIME;
  double FAILURE_RISK;
};

#endif
