#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace skuratov
{
  struct Delimiter
  {
    const char expected;
  };
  std::istream& operator>>(std::istream& in, const Delimiter&& exp);
}

#endif
