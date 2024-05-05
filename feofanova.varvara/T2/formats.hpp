#ifndef FORMATS_HPP
#define FORMATS_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <bitset>
#include <iostream>

namespace feofanova
{
  struct litI
  {
    double& value;
  };
  std::istream& operator>>(std::istream& in, litI&& num);

  struct binI
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, binI&& num);
  std::ostream& operator<<(std::ostream& out, unsigned long long src);

  struct StringI
  {
    std::string& str;
  };
  std::istream& operator>>(std::istream& in, StringI&& num);
}

#endif
