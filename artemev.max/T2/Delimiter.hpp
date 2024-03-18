#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace artemev
{
  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, const Delimiter&& value);
}

#endif

