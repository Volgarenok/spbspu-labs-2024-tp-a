#include "delimiter.hpp"
#include <cctype>

template < bool caseChecking >
std::istream& novokhatskiy::operator>>(std::istream& in, Delimiter< caseChecking >&& ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;

  if (caseChecking)
  {
    if (std::tolower(ex.expected) != std::tolower(ex.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  else if (c != ex.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

template < bool caseChecking >
std::istream& novokhatskiy::operator>>(std::istream& in, DelimiterString< caseChecking >&& ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  const char* exp = ex.expected;
  while ((*exp != '\0') && in)
  {
    in >> Delimiter< caseChecking >{ *exp };
    ++exp;
  }
  return in;
}
