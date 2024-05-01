#include "delimeter.hpp"

std::istream& zaparin::operator>>(std::istream& in, Delimeter&& del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char a = 0;
  in >> a;

  if (a != del.expected)
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}