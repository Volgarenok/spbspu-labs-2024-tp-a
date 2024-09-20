#include "delimiter.h"

namespace skopchenko
{

  std::istream &operator>>(std::istream &in, Delimiter &&exp)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    char c = 0;
    for (size_t i = 0; exp.exp[i] && in; ++i)
    {
      in >> c;
      if (c != exp.exp[i])
      {
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }

}
