#ifndef STREAM_GUARD_HPP
#define STREAM_GUARD_HPP
#include <iostream>

namespace spiridonov
{
  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios< char >& s);
    ~StreamGuard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

#endif
