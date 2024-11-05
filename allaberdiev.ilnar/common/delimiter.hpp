#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace allaberdiev
{
  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& exp);

  struct Line
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, Line&& exp);
}
#endif
