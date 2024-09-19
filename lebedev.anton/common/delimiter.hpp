#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace lebedev
{
  struct Delimiter
  {
    char expected;
  };
  std::istream & operator>>(std::istream & input, Delimiter && delimiter);
}

#endif
