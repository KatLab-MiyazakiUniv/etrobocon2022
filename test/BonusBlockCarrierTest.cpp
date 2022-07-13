/**
 * @file BonusBlockCarrierTest.cpp
 * @brief BonusBlockCarrierクラスのテスト
 * @author sugaken0528
 */

#include "BonusBlockCarrier.h"
#include "Rotation.h"
#include "StraightRunner.h"
#include "LineTracer.h"
#include "Controller.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {

  // 呼び出すだけのテスト
  TEST(BonusBlockCarrierTest, run)
  {
    Rotation rotation;
    StraightRunner straightRunner;
    LineTracer lineTracer(true);
    Controller controller;
    int targetBrightness = 45;

    // ボーナスブロック運搬を実行
    BonusBlockCarrier::run(targetBrightness);
  }
}  // namespace etrobocon2022_test