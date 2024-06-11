#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace sivkov
{
  struct DelimiterI
  {
    char expected;
  };

  struct DelimiterStr
  {
    const char * expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterI&& exp);
  std::istream& operator>>(std::istream& in, DelimiterStr&& exp);
}

#endif
