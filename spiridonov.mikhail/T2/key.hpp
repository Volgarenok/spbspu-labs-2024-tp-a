#ifndef KEYI_HPP
#define KEYI_HPP
#include <iostream>

namespace spiridonov
{
  struct DblSciI
  {
    double& num;
  };
  struct MantissaI
  {
    double& mantissa;
  };

  struct StringI
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, DblSciI&& dbl);
  std::istream& operator>>(std::istream& in, MantissaI&& mantissa);
  std::istream& operator>>(std::istream& in, StringI&& str);
}

#endif