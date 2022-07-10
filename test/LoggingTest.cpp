/**
 * @file LoggingTest.cpp
 * @brief Loggingクラスをテストする
 * @author sap268
 */

#include "Logging.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {
  TEST(LoggingTest, writeLogs)
  {
    Logging logging;
    logging.writeLogs("write logs test.");
  }

  TEST(LoggingTest, writeWarningMessage)
  {
    Logging logging;
    logging.writeWarningMessage("write WarningMessage test.");
  }

  TEST(LoggingTest, writeErrorMessage)
  {
    Logging logging;
    logging.writeErrorMessage("write ErrorMessage test.");
  }
}  // namespace etrobocon2022_test