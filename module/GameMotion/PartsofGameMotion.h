/**
 * @file PartsofGameMotion.cpp
 * @brief ゲームエリア内動作パラメータ調整用の仮コード
 * @author sap2368
 */

#ifndef PARTS_OF_GAME_MOTION_H
#define PARTS_OF_GAME_MOTION_H

#include "Rotation.h"
#include "LineTracer.h"
#include "StraightRunner.h"
#include "Controller.h"

class PartsofGameMotion {
 public:
  /**
   * コンストラクタ
   */
  PartsofGameMotion();

  /**
   * 中点→交点
   */
  void mp2ip(bool& isLeftEdge, int targetBrightness);

  /**
   * 中点→ブロック
   */
  void mp2b();

  /**
   * 中点→中点
   */
  void mp2mp();

  /**
   * ブロック→交点
   */
  void b2ip();

  /**
   * ブロック→中点
   */
  void b2mp();

  /**
   * 交点→ブロック
   */
  void ip2b();

  /**
   * 交点→中点
   */
  void ip2mp(bool& isLeftEdge, int targetBrightness);

  /**
   * 復帰動作
   */
  void reverse_action(bool& isLeftEdge, int targetBrightness);

  /**
   * 縦調整
   */
  void Vadjustment();

  /**
   * 斜め調整
   */
  void Dadjustment();

 private:
  bool isLeftEdge;       // true:左コース, false: コース
  int targetBrightness;  // 目標輝度
  LineTracer lineTracer;
  StraightRunner straightRunner;
  Controller controller;
  Rotation rotation;
};
#endif
