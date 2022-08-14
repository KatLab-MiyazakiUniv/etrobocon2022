/**
 * @file   EdgeChanger.h
 * @brief  エッジ切り替え
 * @author mutotaka0426
 */

#ifndef EDGE_CHANGER_H
#define EDGE_CHANGER_H

#include "Motion.h"

class EdgeChanger : public Motion {
 public:
  /**
   * コンストラクタ
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   * @param _nextEdge 切り替え後のエッジ(true:左エッジ，false:右エッジ)
   */
  EdgeChanger(bool& _isLeftEdge, bool _nextEdge);

  /**
   * @brief エッジを切り替える
   */
  void run();

  /**
   * @brief 実行のログを取る
   */
  void logRunning();

 private:
  bool& isLeftEdge;  // エッジの左右判定(true:左エッジ, false:右エッジ)
  bool nextEdge;     // 切り替え後のエッジ(true:左エッジ，false:右エッジ)
};

#endif
