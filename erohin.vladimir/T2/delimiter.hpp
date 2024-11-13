#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>
#include <cctype>

namespace erohin
{
  template< bool isCaseSensetive >
  struct Delimiter
  {
    char expected;
  };

  template< bool isCaseSensetive >
  std::istream & operator>>(std::istream & input, Delimiter< isCaseSensetive > && dest)
  {
    std::istream::sentry sentry(input);
    if (!sentry)
    {
      return input;
    }
    char c = 0;
    input >> c;
    bool isExpected = isCaseSensetive && (c == dest.expected);
    bool isIgnoredCaseExpected = !isCaseSensetive && (tolower(c) == tolower(dest.expected));
    if (input && !(isExpected || isIgnoredCaseExpected))
    {
      input.setstate(std::ios::failbit);
    }
    return input;
  }

  template class Delimiter< false >;
  using IgnoredCaseDelimiter = Delimiter< false >;
  template class Delimiter< true >;
  using SensetiveCaseDelimiter = Delimiter< true >;
}

#endif
