/**
 * @file   StringOperator.cpp
 * @brief  StringOperatorクラスのテスト
 * @author mutotaka0426
 */

#include "StringOperator.h"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

namespace etrobocon2022_test {

  TEST(StringOperatorTest, removeEOL)
  {
    char actual[32] = "StringOperator test\n";
    char expected[32] = "StringOperator test";

    // actualの改行を削除
    strcpy(actual, StringOperator::removeEOL(actual));

    // 二つの文字列が等しいことをテスト
    EXPECT_STREQ(expected, actual);
  }

  // 文字列リテラルを入力した場合
  TEST(StringOperatorTest, removeEOLInLiteral)
  {
    char* actual = "StringOperator test\n";
    char* expected = "StringOperator test";

    // actualの改行を削除
    actual = StringOperator::removeEOL(actual);

    // 二つの文字列が等しいことをテスト
    EXPECT_STREQ(expected, actual);
  }

  // 空の文字列を入力とした場合のテスト
  TEST(StringOperatorTest, notRemove)
  {
    char string[64] = "";
    std::string expected = "\x1B[36m";
    expected += "Warning: The parameter passed to StringOperator::removeEOL is empty\n";
    expected += "\x1B[39m";

    testing::internal::CaptureStdout();  // 標準出力キャプチャ開始
    StringOperator::removeEOL(string);
    std::string actual = testing::internal::GetCapturedStdout();  // キャプチャ終了

    // Warningが出ているかテスト
    EXPECT_EQ(expected, actual);
  }
}  // namespace etrobocon2022_test
