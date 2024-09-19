#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP
#include <iostream>

namespace chernov
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
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
