#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>
#include <string>

namespace skuratov
{
  struct Delimiter
  {
    const char expected;
  };
  std::istream& operator>>(std::istream& in, const Delimiter&& exp);

  struct LineDelimiter
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, const LineDelimiter&& exp);
}

#endif
