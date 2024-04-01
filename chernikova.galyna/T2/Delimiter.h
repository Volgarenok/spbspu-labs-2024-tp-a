#ifndef DELIMITER_H
#define DELIMITER_H

#include <iostream>

namespace chernikova
{
  struct DelimiterI
  {
    const char expected;
    bool variability = false;
  };

  struct StringDelimiterI
  {
    const char* exp;
  };
  std::istream& operator>>(std::istream& in, chernikova::DelimiterI&& exp);
  std::istream& operator>>(std::istream& in, chernikova::StringDelimiterI&& dest);
}

#endif
