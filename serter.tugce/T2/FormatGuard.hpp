#ifndef FORMATGUARD_HPP
#define FORMATGUARD_HPP

#include <iostream>

namespace serter
{
  class FormatGuard
  {
    public:
      explicit FormatGuard(std::basic_ios<char>& s);
      ~FormatGuard();
   
    private:
      std::basic_ios<char>& s_;
      std::streamsize precision_;
      std::basic_ios<char>::fmtflags flags_;
  };
}

#endif

