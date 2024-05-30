#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace petrov
{
  struct DelimiterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterI&& dest);
}

#endif
