#ifndef KEYI_HPP
#define KEYI_HPP

#include <iostream>

namespace ayupov
{
  struct DblSciI
  {
    double& num;
  };
  struct MantissaI
  {
    double& mantissa;
  };
  struct CharI
  {
    char& value;
  };
  struct StringI
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, DblSciI&& dbl);
  std::ostream& operator<<(std::ostream& out, DblSciI&& dbl);
  std::istream& operator>>(std::istream& in, MantissaI&& mantissa);
  std::istream& operator>>(std::istream& in, CharI&& chr);
  std::istream& operator>>(std::istream& in, StringI&& str);
}

#endif
