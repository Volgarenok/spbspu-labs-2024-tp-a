#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iosfwd>

namespace erohin
{
  struct Delimeter
  {
    char expected;
    bool isCaseSensetive = true;
  };

  std::istream & operator>>(std::istream & input, Delimeter && dest);
}

#endif
