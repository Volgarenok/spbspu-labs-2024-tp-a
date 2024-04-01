#ifndef DELIMITER_H
#define DELIMITER_H

#include <iostream>

namespace chernikova
{
  struct StringDelimiterI
  {
    const char* exp;
  };

  std::istream& operator>>(std::istream& in, chernikova::StringDelimiterI&& dest);
}

#endif
