#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>
#include <string>

namespace skopchenko
{

  struct DblLit
  {
    double value;
  };

  struct UllOct
  {
    unsigned long long value;
  };

  struct StringVal
  {
    std::string value;
  };

  std::istream &operator>>(std::istream &in, DblLit &&key);
  std::istream &operator>>(std::istream &in, UllOct &&key);
  std::istream &operator>>(std::istream &in, StringVal &&key);

}

#endif
