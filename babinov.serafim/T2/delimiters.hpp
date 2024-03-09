#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP
#include <istream>
#include <string>

namespace babinov
{
  struct CharDelimiterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, CharDelimiterI&& del);
  
  struct StringDelimiterI
  {
    std::string expected;
  };
  std::istream& operator>>(std::istream& in, StringDelimiterI&& del);
}

#endif
