#include "delimiter.hpp"
#include <istream>
#include <string>

std::istream& allaberdiev::operator>>(std::istream& in, Delimiter&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& allaberdiev::operator>>(std::istream& in, Line&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  for (int i = 0; exp.expected[i] != '\0'; i++)
  {
    in >> c;
    if (c != exp.expected[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
