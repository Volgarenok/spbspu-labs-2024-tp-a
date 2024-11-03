#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace kovtun
{
  struct DelimiterI
  {
    char expected;
  };

  std::istream & operator>>(std::istream & in, DelimiterI && delimiter);
}

#endif
