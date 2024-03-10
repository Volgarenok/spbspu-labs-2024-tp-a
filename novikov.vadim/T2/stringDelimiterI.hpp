#ifndef STRING_DELIMITER_I_HPP
#define STRING_DELIMITER_I_HPP

#include <istream>

namespace novikov
{
  struct StringDelimiterI
  {
    const char* expected;
    bool ignoreCase = false;
  };
  std::istream& operator>>(std::istream& in, const StringDelimiterI& exp);
}

#endif
