#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <istream>

namespace novikov
{
  struct CharDelimiterI
  {
    char expected;
    bool ignore_case = false;
  };
  std::istream& operator>>(std::istream& in, const CharDelimiterI& exp);

  struct StringDelimiterI
  {
    const char* expected;
    bool ignore_case = false;
  };
  std::istream& operator>>(std::istream& in, const StringDelimiterI& exp);
}

#endif
