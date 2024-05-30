#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP

#include <iostream>

namespace erohin
{
  class ScopeGuard
  {
  public:
    ScopeGuard(std::basic_ios< char > & stream_);
    ~ScopeGuard();
  private:
    std::basic_ios< char > & stream_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

#endif
