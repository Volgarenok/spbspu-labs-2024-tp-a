#include "Delimeter.hpp"

std::istream & kornienko::operator>>(std::istream & in, const Delimeter && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (std::tolower(c) != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & kornienko::operator>>(std::istream & in, const DelimeterString && exp)
{
  using del = Delimeter;
  for (int i = 0; exp.expected[i] != '\0' && in; ++i)
  {
    in >> del{exp.expected[i]};
  }
  return in;
}
