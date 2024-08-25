#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <istream>

namespace kravchenko
{
  template< bool caseIgnore >
  struct DelimiterI
  {
    const char expected;
  };

  template< bool caseIgnore >
  std::istream& operator>>(std::istream& in, DelimiterI< caseIgnore >&& exp);

  template< bool caseIgnore >
  struct StringDelimiterI
  {
    const char* expected;
  };

  template< bool caseIgnore >
  std::istream& operator>>(std::istream& in, StringDelimiterI< caseIgnore >&& exp);
}

template< bool caseIgnore >
std::istream& kravchenko::operator>>(std::istream& in, DelimiterI< caseIgnore >&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (caseIgnore)
  {
    if (std::tolower(c) != std::tolower(exp.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  else if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

template< bool caseIgnore >
std::istream& kravchenko::operator>>(std::istream& in, StringDelimiterI< caseIgnore >&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (std::size_t i = 0; exp.expected[i] && in; ++i)
  {
    in >> DelimiterI< caseIgnore >{ exp.expected[i] };
  }
  return in;
}

#endif
