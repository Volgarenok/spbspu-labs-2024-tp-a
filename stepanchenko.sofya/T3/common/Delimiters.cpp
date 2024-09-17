#include <cstring>

#include <Delimiters.hpp>

std::istream& stepanchenko::operator>>(std::istream& in, DelimiterI&& del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (isalpha(c))
  {
    tolower(c);
  }
  if (c != del.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& stepanchenko::operator>>(std::istream& in, StringDelimiterI&& del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  for (size_t i = 0; del.expected[i] && in; ++i)
  {
    char c = 0;
    in >> c;
    tolower(c);
    if (c != del.expected[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

