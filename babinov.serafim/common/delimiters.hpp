#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP
#include <istream>

namespace babinov
{
  struct CharDelimiterI
  {
    char expected;
    bool caseSensitive;

    static CharDelimiterI sensitive(char exp);
    static CharDelimiterI insensitive(char exp);
  private:
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

    static StringDelimiterI sensitive(const char* exp);
    static StringDelimiterI insensitive(const char* exp);
  private:
    StringDelimiterI(const char* exp, bool caseSens = true):
      expected(exp),
      caseSensitive(caseSens)
    {}
  };
  std::istream& operator>>(std::istream& in, StringDelimiterI&& del);
}

#endif
