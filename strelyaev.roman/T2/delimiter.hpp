#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>
#include <string>
namespace strelyaev
{
  struct delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, delimiter&& exp);
}
#endif
