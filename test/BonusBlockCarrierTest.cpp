/**
 * @file BonusBlockCarrierTest.cpp
 * @brief BonusBlockCarrierクラスのテスト
 * @author sugaken0528
 */

#include "BonusBlockCarrier.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {

  // 呼び出すだけのテスト
  TEST(BonusBlockCarrierTest, run)
  {
    int targetBrightness = 45;

    // ボーナスブロック運搬を実行
    BonusBlockCarrier::run(targetBrightness);
  }
}  // namespace etrobocon2022_test