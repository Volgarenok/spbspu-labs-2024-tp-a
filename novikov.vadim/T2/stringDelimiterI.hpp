#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <istream>

namespace novikov
{
  struct StringDelimiterI
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, const DelimiterI& exp);
}

#endif