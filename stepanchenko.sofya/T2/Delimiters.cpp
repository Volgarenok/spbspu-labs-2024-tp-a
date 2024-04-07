#include "Delimiters.hpp"

std::istream& stepanchenko::operator>>(std::istream& in, DelimeterI&& del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  std::tolower(c);
  if (c != del.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
