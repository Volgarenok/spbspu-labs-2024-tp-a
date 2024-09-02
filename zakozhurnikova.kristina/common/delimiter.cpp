#include "delimiter.hpp"

std::istream& zakozhurnikova::operator>>(std::istream& in, const DelimiterChar&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  in >> c;
  c = std::tolower(c);
  if (c != exp.delimiter)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & zakozhurnikova::operator>>(std::istream & in, DelimiterString&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t i = 0;
  while (exp.delimiter[i] != '\0')
  {
    in >> DelimiterChar{exp.delimiter[i]};
    ++i;
  }
  return in;
}
