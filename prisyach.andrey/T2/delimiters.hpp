#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <iostream>

namespace prisyach
{
  struct DelimiterChar
  {
    char delimeter;
  };

  struct DelimiterString
  {
    const char * delimeter;
  };

  std::istream & operator>>(std::istream & in, DelimiterChar && del);
  std::istream & operator>>(std::istream & in, DelimiterString && del);
}

#endif
