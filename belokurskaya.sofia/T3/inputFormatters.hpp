#ifndef INPUT_FORMATTERS_HPP
#define INPUT_FORMATTERS_HPP

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
