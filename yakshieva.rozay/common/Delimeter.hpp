#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iostream>

namespace yakshieva
{
  struct DelimeterIO
  {
    char delimeter;
  };

  std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
}

#endif
