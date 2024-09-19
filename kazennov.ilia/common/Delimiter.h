#ifndef DELIMITER_H
#define DELIMITER_H

#include <iostream>

namespace kazennov
{
  struct Delimiter
  {
    char expected;
  };
  struct StringDelimiter
  {
    const char* expected;
  };

  std::istream& operator>>(std::istream& in, Delimiter&& exp);
  std::istream& operator>>(std::istream& in, StringDelimiter&& exp);
}
#endif
