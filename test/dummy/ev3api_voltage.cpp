/**
 * @file ev3api_voltage.cpp
 * @brief 電圧取得関数のダミー
 * @author sugaken0528
 */

#include "ev3api_voltage.h"

float ev3_battery_voltage_mV()
{
  // SPIKEの電圧の標準値[mV]
  return 7300;
}