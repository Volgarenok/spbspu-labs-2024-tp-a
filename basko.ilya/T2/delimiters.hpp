#ifndef DELIMITERS_H
#define DELIMITERS_H

#include <iostream>

namespace basko
{
  struct DelimiterChar
  {
    char expected;
  };
  std::istream & operator>>(std::istream& in, DelimiterChar&& exp);

  struct DelimiterString
  {
    const char * expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterString&& exp);
}

#endif
