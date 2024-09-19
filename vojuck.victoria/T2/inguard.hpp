#ifndef INGUARD_HPP
#define INGUARD_HPP

#include <iostream>

namespace vojuck
{
  class InGuard
  {
  public:
    InGuard(std::basic_ios< char > &s);
    ~InGuard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
