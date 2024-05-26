#ifndef FORMATS_HPP
#define FORMATS_HPP
#include <istream>

namespace demin
{
  struct DblLit
  {
    double &value;
  };
  std::istream &operator>>(std::istream &in, DblLit &&key);

  struct UllOct
  {
    unsigned long long &value;
  };
  std::istream &operator>>(std::istream &in, UllOct &&key);

  struct StringVal
  {
    std::string &value;
  };
  std::istream &operator>>(std::istream &in, StringVal &&key);
}
#endif
