/**
 * @file ColorBlockCarrierTest.cpp
 * @brief ColorBlockCarrierクラスのテスト
 * @author sap2368
 */

#include "ColorBlockCarrier.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {

  // 呼び出すだけのテスト
  TEST(ColorBlockCarrierTest, run)
  {
    int targetBrightness = 45;

    // ボーナスブロック運搬を実行
    ColorBlockCarrier::run(targetBrightness);
  }
}  // namespace etrobocon2022_test