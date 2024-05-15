#ifndef STREAM_GUARD_HPP
#define STREAM_GUARD_HPP

#include <iostream>
#include <iomanip>

namespace belokurskaya
{
  class StreamGuard
  {
  public:
    StreamGuard(std::ios& stream);
    ~StreamGuard();

  private:
    std::ios& stream_;
    std::ios::fmtflags state_;
    std::streamsize precision_;
    char fill_;
  };
}

#endif
