#ifndef DELIMITER_H
#define DELIMITER_H

#include <iostream>

namespace chernikova
{
  struct DelimiterChar
  {
    const char expected;
  };
  std::istream& operator>>(std::istream& in, chernikova::DelimiterChar&& exp);
}

#endif
