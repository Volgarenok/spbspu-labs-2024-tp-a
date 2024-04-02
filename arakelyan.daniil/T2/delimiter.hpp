#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>
#include <string>

namespace arakelyan
{
  struct DelimiterIO
  {
    char exp;
  };
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
}

#endif
