#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP
#include <string>
#include <iostream>

namespace chernov
{
  struct DoubleIO
  {
    double& value_;
  };

  struct UnsignedLongLongIO
  {
    unsigned long long& value_;
  };

  struct CharIO
  {
    char value_;
  };

  struct StringIO
  {
    std::string value_;
  };

  std::istream& operator>>(std::istream& in, CharIO&& exp);
  std::istream& operator>>(std::istream& in, DoubleIO&& exp);
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& exp);
  std::istream& operator>>(std::istream& in, StringIO&& exp);
  std::string convertDoubleToCalcDouble(double number);
}

#endif
