/**
 * @file EtRobocon2022Test.cpp
 * @brief EtRobocon2022クラスのテストケース
 * @author sakakibara
 */

#include "../module/EtRobocon2022.h" // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2022_test
{

    class EtRobocon2022Test : public ::testing::Test
    {
        friend class EtRobocon2022;

    protected:
        virtual void SetUp() {}
        EtRobocon2022 et;
    };

    TEST_F(EtRobocon2022Test, startTest) {}
} // namespace etrobocon2022_test