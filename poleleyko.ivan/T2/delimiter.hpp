#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace poleleyko
{
  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& exp);

  struct StringDelimiter
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, StringDelimiter&& exp);
}
#endif
