#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iosfwd>

namespace erohin
{
  struct Delimeter
  {
    char expected;
  };

  std::istream & operator>>(std::istream & input, Delimeter && dest);
}

#endif
