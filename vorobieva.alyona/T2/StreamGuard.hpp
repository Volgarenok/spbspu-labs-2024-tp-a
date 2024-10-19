#ifndef STREAM_GUARD_HPP
#define STREAM_GUARD_HPP

#include <iostream>

namespace vorobieva {
class StreamGuard {
public:
  explicit StreamGuard(std::basic_ios<char> &stream);
  ~StreamGuard();

private:
  std::basic_ios<char> &stream_;
  std::streamsize precision_;
  std::basic_ios<char>::fmtflags flags_;
};
} // namespace vorobieva

#endif
