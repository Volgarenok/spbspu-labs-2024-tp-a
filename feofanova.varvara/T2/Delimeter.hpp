#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <iostream>

namespace feofanova
{
  struct DelimeterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, DelimeterI&& exp);

  struct IgnoreCaseDelimeter
  {
    const char* expectation;
  };
  std::istream& operator>>(std::istream&, const IgnoreCaseDelimeter&&);
}

#endif

