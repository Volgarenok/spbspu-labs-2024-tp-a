#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace strelyaev
{
  struct delimiter_t
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, delimiter_t&& exp);
}
#endif
