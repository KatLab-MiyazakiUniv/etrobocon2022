/**
 * @file LoggerTest.cpp
 * @brief Loggerクラスをテストする
 * @author sap268
 */

#include "Logger.h"
#include <gtest/gtest.h>

namespace etrobocon2022_test {
  TEST(LoggerTest, writeLogs)
  {
    Logger logger;
    logger.log("logs test.");
  }

  TEST(LoggingTest, writeWarningMessage)
  {
    Logger logger;
    logger.logWarning("WarningMessage test.");
  }

  TEST(LoggingTest, writeErrorMessage)
  {
    Logger logger;
    logger.logError("ErrorMessage test.");
  }

  TEST(LoggingTest, writeHighlightLog)
  {
    Logger logger;
    logger.logHighlight("HighlightLog test.");
  }

}  // namespace etrobocon2022_test
