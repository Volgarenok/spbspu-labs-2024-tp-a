#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace chernikova
{
  struct ExactSymbolI
  {
    const char expected;
  };

  struct ExactSymbolSavedI
  {
    const char expected;
    char& real;
  };

  struct AnySymbolI
  {
    const char* expected;
    char& real;
  };

  struct DelimiterI
  {
    const char expected;
    bool upperСase = false;
  };

  struct StringDelimiterI
  {
    const char* exp;
  };

  std::istream& operator>>(std::istream& in, ExactSymbolI&& exp);
  std::istream& operator>>(std::istream& in, ExactSymbolSavedI&& exp);
  std::istream& operator>>(std::istream& in, AnySymbolI&& exp);
  std::istream& operator>>(std::istream& in, DelimiterI&& exp);
  std::istream& operator>>(std::istream& in, StringDelimiterI&& dest);
}

#endif
