/**
 * @file ev3api_motor.h
 * @brief モータ関連の列挙体（ダミー）
 * @author sap2368
 */
#pragma once

/**
 * @brief モータポートを表す番号
 */
typedef enum {
  EV3_PORT_A = 0,      //ポートA
  EV3_PORT_B = 1,      //ポートB
  EV3_PORT_C = 2,      //ポートC
  EV3_PORT_D = 3,      //ポートD
  TNUM_MOTOR_PORT = 4  //モータポートの数
} motor_port_t;

/**
 * @brief サポートするモータタイプ
 */
typedef enum {
  NONE_MOTOR = 0,     //モータ未接続
  MEDIUM_MOTOR,       //サーボモータM
  LARGE_MOTOR,        //サーボモータL
  UNREGULATED_MOTOR,  //未調整モータ
  TNUM_MOTOR_TYPE     //モータタイプの数
} motor_type_t;
