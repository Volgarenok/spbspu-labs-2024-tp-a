#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

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
