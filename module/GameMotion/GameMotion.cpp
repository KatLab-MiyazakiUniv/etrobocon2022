/**
 * @file GameMotion.cpp
 * @brief ゲーム動作の親クラス
 * @author kodama0720
 */

#include "GameMotion.h"

GameMotion::GameMotion(bool& isLeftEdge, double time, double risk)
  : MOTION_TIME(time), FAILURE_RISK(risk)
{
  LineTracer lineTracer(&isLeftEdge);
};

//動作時間の取得
double GameMotion::getMotionTime(void)
{
  return MOTION_TIME;
}

//失敗リスクの取得
double GameMotion::getFailureRisk(void)
{
  return FAILURE_RISK;
}
