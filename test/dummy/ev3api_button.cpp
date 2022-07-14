/**
 * @file ev3api_button.cpp
 * @brief ボタン関連のダミー
 * @author mutotaka0426
 */

#include "ev3api_button.h"

bool ev3_button_is_pressed(button_t button)
{
  // 左ボタン，右ボタン，中央ボタンがランダムに押される想定
  int num = rand() % 3;

  // 左ボタンが押された時（num=0）
  if(button == LEFT_BUTTON && num == 0) return true;

  // 右ボタンが押された時（num=1）
  if(button == RIGHT_BUTTON && num == 1) return true;

  // 中央ボタンが押された時（num=2）
  if(button == ENTER_BUTTON && num == 2) return true;

  if(button != LEFT_BUTTON && button != RIGHT_BUTTON && button != ENTER_BUTTON) {
    printf("\x1b[31m");  // 前景色を赤に
    printf("error: Variable \"button\" is an unexpected value");
    printf("\x1b[39m\n");  // 前景色をデフォルトに戻す
  }

  return false;
}
