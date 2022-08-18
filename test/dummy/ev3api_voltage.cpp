/**
 * @file ev3api_voltage.cpp
 * @brief 電圧取得関数のダミー
 * @author sugaken0528
 */

#include "ev3api_voltage.h"

int ev3_battery_voltage_mV()
{
  int index = rand() % 2;
  switch(index) {
    case 0:
      return 7300;  // SPIKEの電圧の標準値[mV]
    case 1:
      return 4196;  // SPIKEの電圧の最大値の半分[mV]
  }
}