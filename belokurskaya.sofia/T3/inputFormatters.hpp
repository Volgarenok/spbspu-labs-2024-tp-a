#ifndef INPUTFORMATTERS_HPP
#define INPUTFORMATTERS_HPP

#include <iostream>

namespace belokurskaya
{
  struct DelimiterI
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterI&& dest);
}

#endif
