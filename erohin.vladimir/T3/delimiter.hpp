#ifndef DELIMITER_HPP
#define DELIMITER_HPP

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
