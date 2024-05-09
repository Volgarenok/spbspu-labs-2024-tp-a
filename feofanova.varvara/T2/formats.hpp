#ifndef FORMATS_HPP
#define FORMATS_HPP
#include <iostream>
#include <bitset>

namespace feofanova
{
  struct LitI
  {
    double& value;
  };
  std::istream& operator>>(std::istream& in, litI&& num);

  struct BinI
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, binI&& num);

  struct BinO
  {
    unsigned long long value;
  };
  std::ostream& operator<<(std::ostream& out, binO&& src);

  struct StringI
  {
    std::string& str;
  };
  std::istream& operator>>(std::istream& in, StringI&& num);
}

#endif
