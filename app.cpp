/**
 * @file app.cpp
 * @brief タスクを管理するクラス
 * @author miyashita64
 */

#include "EtRobocon2022.h"
#include "app.h"

// メインタスク
void main_task(intptr_t unused)
{
  EtRobocon2022::start();
  ext_tsk();
}
