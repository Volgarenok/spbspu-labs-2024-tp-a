#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <iostream>

namespace feofanova
{
  struct delimeter_t
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, delimeter_t&& exp);

  struct IgnoreCaseDelimeter
  {
    const char* expectation;
  };
  std::istream& operator>>(std::istream&, const IgnoreCaseDelimeter&&);
}

#endif
