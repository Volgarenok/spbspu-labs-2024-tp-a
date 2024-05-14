#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <istream>

namespace felk
{
  struct Delimeter
  {
    char exp;
    bool caseStrict;
    explicit Delimeter(char exp, bool strict = true);
  };

  struct WrapperLL
  {
    long long& data;
  };

  struct WrapperHex
  {
    size_t& data;
  };

  struct WrapperStr
  {
    std::string& data;
  };

  std::istream& operator>>(std::istream& in, Delimeter&& exp);
  std::istream& operator>>(std::istream& in, WrapperLL&& exp);
  std::istream& operator>>(std::istream& in, WrapperHex&& exp);
  std::istream& operator>>(std::istream& in, WrapperStr&& exp);
}
#endif
