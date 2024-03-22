#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <iosfwd>

namespace erohin
{
  struct DoubleFormat
  {
    double & ref;
  };

  struct LongLongFormat
  {
    long long & ref;
  };

  struct StringFormat
  {
    std::string & ref;
  };

  std::istream & operator>>(std::istream & input, DoubleFormat && dest);
  std::istream & operator>>(std::istream & input, LongLongFormat && dest);
  std::istream & operator>>(std::istream & input, StringFormat && dest);
}

#endif
