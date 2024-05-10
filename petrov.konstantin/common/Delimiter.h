#ifndef DELIMITR_H
#define DELIMITR_H

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
