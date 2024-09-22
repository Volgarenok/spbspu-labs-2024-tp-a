#ifndef IOSCOPEGUARD_HPP
#define IOSCOPEGUARD_HPP

#include <iostream>

namespace kovtun
{
  class IOScopeGuard
  {
  public:
    IOScopeGuard(std::basic_ios< char > & s);
    ~IOScopeGuard();

  private:
    std::basic_ios< char > & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

#endif
