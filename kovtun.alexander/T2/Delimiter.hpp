#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace kovtun
{
  struct DelimiterI
  {
    char expected;
  };

  struct KeyI
  {
    int & number;
  };

  std::istream & operator>>(std::istream & in, DelimiterI && delimiter);
  std::istream & operator>>(std::istream & in, KeyI && keyStub);
}

#endif
