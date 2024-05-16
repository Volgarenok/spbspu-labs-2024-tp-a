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
}
#endif // !DELIMITER_H
