#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>
namespace strelyaev
{
  struct delimiter
  {
    const char expected;
  };
  std::istream& operator>>(std::istream&& in, const delimiter&& delimiter);
}
#endif
