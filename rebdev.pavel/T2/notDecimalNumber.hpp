#ifndef NOTDECIMALNUMBER_HPP
#define NOTDECIMALNUMBER_HPP

#include <iostream>

namespace rebdev
{
  struct notDecimalNumber_t
  {
    unsigned long long data_;
    size_t size_;
    char basisOfNumSys_;
  };

  std::istream & operator >> (std::istream & in, notDecimalNumber_t  & num);
  std::ostream & operator << (std::ostream & out, notDecimalNumber_t & num);

  bool isCharInNumSys(char c, char basisOfNumSys);
  unsigned long long charToULL(char c);
  char ULLToChar(unsigned long long c);
}

#endif
