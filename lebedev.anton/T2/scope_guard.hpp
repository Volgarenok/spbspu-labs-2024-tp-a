#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP

#include <iostream>

namespace lebedev
{
  class StreamGuard
  {
  public:
    explicit StreamGuard(std::basic_ios< char > & s);
    ~StreamGuard();
  private:
    std::basic_ios< char > & s_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

#endif
