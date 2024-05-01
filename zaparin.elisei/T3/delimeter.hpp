#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iostream>

namespace zaparin
{
  struct Delimeter
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, Delimeter&& del);
}

#endif

