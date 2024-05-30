#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <string>
#include <iostream>

namespace kozakova
{
  struct DelimiterString
  {
    std::string expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterString&& exp);

  struct DelimiterChar
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterChar&& exp);
}

#endif
