#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP

#include <iostream>

namespace vyzhanov
{
  class StreamGuard
  {
  public:
    explicit StreamGuard(std::basic_ios< char >&);
    ~StreamGuard();
  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

#endif
