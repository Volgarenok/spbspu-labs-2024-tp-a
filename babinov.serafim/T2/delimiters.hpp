#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP
#include <istream>

namespace babinov
{
  struct CharDelimiterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, CharDelimiterI&& del);

  struct StringDelimiterI
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, StringDelimiterI&& del);

  struct CharCaseDelimiterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, CharCaseDelimiterI&& del);

  struct StringCaseDelimiterI
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, StringCaseDelimiterI&& del);
}

#endif
