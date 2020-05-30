// Copyright (c) 2020 chrisxiong

#include <string>

#include "gtest/gtest.h"
#include "string_logger/string_logger.h"

using std::string;

TEST(StringLogger, CheckMacro) {
  slogger::StringLogger logger;
  logger.LOG_VVV("trace, name:%s, age:%d", "chrisxiong", 16);
  string log_content = logger.LogContent();
  EXPECT_EQ("[string_logger/string_logger_test.cc][12][TestBody]trace, name:chrisxiong, age:16",  // NOLINT
            log_content);
}

TEST(StringLogger, CheckSimpleLogInfo) {
  slogger::StringLogger logger;
  logger.Log("trace, name:%s, age:%d", "chrisxiong", 16);
  string log_content = logger.LogContent();
  EXPECT_EQ("trace, name:chrisxiong, age:16", log_content);
}

TEST(StringLogger, CheckExceedLimitLogInfo) {
  slogger::StringLogger logger;
  // 4093长度字符正常写入
  string len4093(4093, 'a');
  logger.Log("%s", len4093.c_str());
  string log_content = logger.LogContent();
  EXPECT_EQ(4093, log_content.length());

  // 4096个字符将超出长度，d会被截断
  string len3 = "bcd";
  logger.Log("%s", len3.c_str());
  log_content = logger.LogContent();
  EXPECT_EQ(4096, len4093.length() + len3.length());
  EXPECT_EQ(4095, log_content.length());
  EXPECT_EQ('a', log_content[4092]);
  EXPECT_EQ('b', log_content[4093]);
  EXPECT_EQ('c', log_content[4094]);
  EXPECT_EQ('\0', log_content[4095]);

  // 再增加一个，则会清空原有的内容
  string len1 = "e";
  logger.Log("%s", len1.c_str());
  log_content = logger.LogContent();
  EXPECT_EQ(1, log_content.length());
  EXPECT_EQ('e', log_content[0]);
  EXPECT_EQ('\0', log_content[1]);
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
