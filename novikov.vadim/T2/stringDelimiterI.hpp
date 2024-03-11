#ifndef STRING_DELIMITER_I_HPP
#define STRING_DELIMITER_I_HPP

#include <istream>

namespace novikov
{
  struct StringDelimiterI
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, const StringDelimiterI& exp);

  struct IgnoreCaseStringDelimiterI
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, const IgnoreCaseStringDelimiterI& exp);
}

#endif
