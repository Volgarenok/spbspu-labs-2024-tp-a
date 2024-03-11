#ifndef CHAR_DELIMITER_I_HPP
#define CHAR_DELIMITER_I_HPP

#include <istream>

namespace novikov
{
  struct CharDelimiterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, const CharDelimiterI& exp);

  struct IgnoreCaseCharDelimiterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, const IgnoreCaseCharDelimiterI& exp);
}

#endif
