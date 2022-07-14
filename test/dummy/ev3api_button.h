/**
 * @file ev3api_button.h
 * @brief ボタン関連のダミー
 * @author mutotaka0426
 */

#ifndef EV3API_BUTTON_H
#define EV3API_BUTTON_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief ボタンを表す番号
 */
typedef enum {
  LEFT_BUTTON = 0,   // 左ボタン
  RIGHT_BUTTON = 1,  // 右ボタン
  UP_BUTTON = 2,     // Spikeでは使えないけど一応
  DOWN_BUTTON = 3,   // Spikeでは使えないけど一応
  ENTER_BUTTON = 4,  // 中央ボタン
  BACK_BUTTON = 5,   // Spikeでは使えないけど一応
  TNUM_BUTTON = 6    // Spikeでは使えないけど一応
} button_t;

bool ev3_button_is_pressed(button_t button);

#endif
