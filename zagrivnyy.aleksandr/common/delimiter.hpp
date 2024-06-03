#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace zagrivnyy
{
  struct DelimiterI
  {
    const char *expected;
  };

  std::istream &operator>>(std::istream &in, DelimiterI &&exp);
}

#endif
