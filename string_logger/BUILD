# string_ogger

cc_library(
  name = "string_logger",
  srcs = [
    "string_logger.h",
  ],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "string_logger_test",
  srcs = [
    "string_logger_test.cc",
  ],
  deps = [
    "//string_logger:string_logger",
    "@gtest//:gtest",
  ],
)
