/**
 * @file app.cpp
 * @brief タスクを管理するクラス
 * @author miyashita64
 */

#include "EtRobocon2022.h"
#include "ArmKeeper.h"
#include "app.h"

// メインタスク
void main_task(intptr_t unused)
{
  EtRobocon2022::start();
  ext_tsk();
}

// アームを一定に保つタスク
void arm_task(intptr_t unused)
{
  // ArmKeeper::start();
  ext_tsk();
}