/**
 * @file ev3api_voltage.h
 * @brief 電圧取得関数のダミー
 * @author sugaken0528
 */

#ifndef EV3API_VOLTAGE_H
#define EV3API_VOLTAGE_H

#include <stdlib.h>

/**
 * @brief SPIKEの電圧を取得
 * @return SPIKEの電圧[mV]
 */
int ev3_battery_voltage_mV();

#endif