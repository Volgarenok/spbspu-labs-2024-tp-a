#include "delimiter.hpp"

std::istream& zakozhurnikova::operator>>(std::istream& in, const Delimiter&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t i = 0;
  while (in && exp.delimiter[i])
  {
    char c = 0;
    in >> c;
    if (c == ' ')
    {
      continue;
    }
    if (c == '\n')
    {
      in.setstate(std::ios::badbit);
      return in;
    }
    if (std::tolower(c) != std::tolower(exp.delimiter[i++]))
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
