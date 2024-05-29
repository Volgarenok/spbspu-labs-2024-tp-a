#ifndef DELIMETERS_HPP
#define DELIMETERS_HPP
#include <istream>
#include <cctype>

namespace ravinskij
{
  template < bool isStrictCase >
  struct CharDelimeter
  {
    char expected;
  };

  template < bool isStrictCase >
  std::istream& operator>>(std::istream& in, const CharDelimeter< isStrictCase >& exp)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char ch{};
    in >> ch;
    if ((isStrictCase && (ch != exp.expected)) || (std::tolower(ch) != std::tolower(exp.expected)))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

}
#endif
