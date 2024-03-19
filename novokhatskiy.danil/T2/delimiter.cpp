#include "delimiter.hpp"

std::istream &novokhatskiy::operator>>(std::istream &in, Delimiter &&ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != ex.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &novokhatskiy::operator>>(std::istream &in, DelimiterAlpha &&ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  /* ex.expected = std::tolower(ex.expected); */
  if (std::tolower(c) != std::tolower(ex.expected))
  {
    in.setstate(std::ios::failbit);
  }
  /* else if (c != ex.expected)
  {
    in.setstate(std::ios::failbit);
  } */
  return in;
}

std::istream &novokhatskiy::operator>>(std::istream &in, DelimiterString &&ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  const char *exp = ex.expected;
  while ((*exp != '\0') && in)
  {
    in >> Delimiter{*exp};
    ++exp;
  }
  return in;
}

std::istream &novokhatskiy::operator>>(std::istream &in, DelimiterAlphaString &&ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  const char *exp = ex.expected;
  while ((*exp != '\0') && in)
  {
    in >> DelimiterAlpha{*exp};
    ++exp;
  }
  return in;
}
