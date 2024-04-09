#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <istream>

namespace felk
{
  struct Delimeter
  {
    char exp;
    bool caseStrict;
    Delimeter(char exp, bool strict = true);
  };
  std::istream& operator>>(std::istream& in, Delimeter&& exp);
}

#endif