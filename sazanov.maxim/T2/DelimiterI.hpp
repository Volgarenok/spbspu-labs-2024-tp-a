#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <string>
#include <iostream>

namespace sazanov
{
  template< bool isAnyCase >
  struct DelimiterI
  {
    const char expected;
  };

  template< bool isAnyCase >
  std::istream& operator>>(std::istream& in, DelimiterI< isAnyCase >&& exp)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    char c = 0;
    in >> c;
    if (((c != exp.expected) && !isAnyCase) || (std::tolower(c) != std::tolower(exp.expected)))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  template< bool isAnyCase >
  struct StringDelimiterI
  {
    const char* expected;
  };

  template< bool isAnyCase >
  std::istream& operator>>(std::istream& in, StringDelimiterI< isAnyCase >&& exp)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    while (*exp.expected != '\0')
    {
      in >> DelimiterI< isAnyCase >{*exp.expected};
      ++exp.expected;
    }
    return in;
  }

  using AnyCaseDelimiterI = DelimiterI< true >;
  using StrictCaseDelimiterI = DelimiterI< false >;
  using AnyCaseStringDelimiterI = StringDelimiterI< true >;
  using StrictCaseStringDelimiterI = StringDelimiterI< false >;
}

#endif
