#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP
#include <istream>

namespace babinov
{
  struct CharDelimiterI
  {
    char expected;
    bool caseSensitive;

    CharDelimiterI(char exp, bool caseSens = true):
      expected(exp),
      caseSensitive(caseSens)
    {}
  };
  std::istream& operator>>(std::istream& in, CharDelimiterI&& del);

  struct StringDelimiterI
  {
    const char* expected;
    bool caseSensitive;

    StringDelimiterI(const char* exp, bool caseSens = true):
      expected(exp),
      caseSensitive(caseSens)
    {}
  };
  std::istream& operator>>(std::istream& in, StringDelimiterI&& del);
}

#endif
