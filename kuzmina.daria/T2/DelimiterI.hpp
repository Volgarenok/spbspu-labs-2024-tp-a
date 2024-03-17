#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <iostream>

namespace kuzmina
{
  struct DelimiterI
  {
    char expected;
  };

  std::istream& operator>>(std::istream&, DelimiterI&&);
}

#endif
