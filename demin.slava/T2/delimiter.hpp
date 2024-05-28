#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace demin
{
  struct Delimiter
  {
    const char *exp;
  };
  std::istream &operator>>(std::istream &in, Delimiter &&exp);
}

#endif
