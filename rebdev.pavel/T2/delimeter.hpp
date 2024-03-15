#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <istream>

namespace rebdev
{
  struct delimeter
  {
    char expectedChar;
  };

  std::istream & operator >> (std::istream & in, delimeter && exp);
}

#endif
