#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <istream>

namespace piyavkin
{
  struct Delimeter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimeter&& exp);
}
#endif