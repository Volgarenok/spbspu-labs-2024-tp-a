#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <iosfwd>

namespace erohin
{
  struct DoubleFormat
  {
    double & ref;
  };
  std::istream & operator>>(std::istream & input, DoubleFormat && dest);
}

#endif
