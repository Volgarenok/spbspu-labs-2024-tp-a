#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace timchishina
{
  struct Delimiter
  {
    char expected;
  };
  std::istream & operator>>(std::istream & in, Delimiter && exp);
}
#endif
