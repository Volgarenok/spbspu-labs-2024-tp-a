#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iosfwd>

namespace erohin
{
  struct Delimiter
  {
    char expected;
  };
  std::istream & operator>>(std::istream & input, Delimiter && dest);
}

#endif
