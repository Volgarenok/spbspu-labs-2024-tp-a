#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <istream>
#include "streamGuard.hpp"

namespace ibragimov
{
  template < class S >
  struct DelimiterI
  {
    const char* expectation;
  };
  template < class S >
  std::istream& operator>>(std::istream&, const DelimiterI< S >&&);

  struct CaseSensitive
  {
    static bool isSame(const char, const char);
  };

  struct CaseInsensitive
  {
    static bool isSame(const char, const char);
  };

  template < class S >
  std::istream& operator>>(std::istream& in, const DelimiterI< S >&& value)
  {
    std::istream::sentry guard(in);
    if (guard)
    {
      StreamGuard sGuard(in);
      char c = '\0';
      in >> std::noskipws;
      for (size_t i = 0; value.expectation[i] != '\0'; ++i)
      {
        in >> c;
        if ((in) && (!S::isSame(c, value.expectation[i])))
        {
          in.setstate(std::ios::failbit);
        }
      }
    }
    return in;
  }
}

#endif
