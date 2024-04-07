#ifndef DELIMITER_H
#define DELIMITER_H

#include <iostream>

namespace kazennov {
  struct Delimiter {
    char expected;
  };
  struct StringDelimiter {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, const Delimiter&& exp);
  std::istream& operator>>(std::istream& in, const StringDelimiter&& exp);
}
#endif // !DELIMITER_H
