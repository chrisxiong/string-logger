// Copyright (c) 2020 chrisxiong

#ifndef STRING_LOGGER_STRING_LOGGER_H_
#define STRING_LOGGER_STRING_LOGGER_H_

#include <cstdarg>
#include <cstdio>
#include <cstring>

#define LOG_VVV(fmt, args...) Log("[%s][%d][%s]" fmt, __FILE__, __LINE__, __FUNCTION__, ##args)  // NOLINT
#define LOG_VV(fmt, args...) Log("[%d][%s]" fmt, __LINE__, __FUNCTION__, ##args)
#define LOG_V(fmt, args...) Log("[%d]" fmt, __LINE__, ##args)

namespace slogger {

class StringLogger {
 public:
  StringLogger()
    : buffer_{0},
      buffer_used_len_(0) {}

 public:
  void Log(const char* fmt, ...) {
    const int kBufferLen = sizeof(buffer_);
    if (buffer_used_len_ >= kBufferLen - 1) {
      buffer_used_len_ = 0;
    }
    va_list ap;
    va_start(ap, fmt);
    buffer_used_len_ += vsnprintf(buffer_ + buffer_used_len_,
                                  kBufferLen - buffer_used_len_, fmt, ap);
    if (buffer_used_len_ >= kBufferLen - 1) {
      buffer_used_len_ = kBufferLen - 1;
    }
    *(buffer_ + buffer_used_len_) = '\0';
    va_end(ap);
  }
  const char* LogContent() {
    return buffer_;
  }

 private:
  char buffer_[4096];
  int buffer_used_len_;
};

}  // namespace slogger

#endif  // STRING_LOGGER_STRING_LOGGER_H_
