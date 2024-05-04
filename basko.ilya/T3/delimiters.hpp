#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <iostream>

namespace basko
{
  struct DelimiterChar
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterChar&& exp);
}

#endif
