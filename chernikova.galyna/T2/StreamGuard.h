#ifndef STREAM_GUARD_H
#define STREAM_GUARD_H

#include <iostream>

class StreamGuard
{
public:
  StreamGuard(std::basic_ios<char>& s):
    s_(s),
    precision_(s.precision()),
    flags_(s.flags())
  {}

  ~StreamGuard()
  {
    s_.precision(precision_);
    s_.flags(flags_);
  }

private:
  std::basic_ios<char>& s_;
  std::streamsize precision_;
  std::basic_ios<char>::fmtflags flags_;
};

#endif
