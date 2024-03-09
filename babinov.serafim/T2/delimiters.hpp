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
    char* expected;
  };
  std::istream& operator>>(std::istream& in, StringDelimiterI&& del);
}

#endif
