#include "delimeter.hpp"

std::istream& zaparin::operator>>(std::istream& in, Delimeter&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  size_t i = 0;
  while (in && exp.expected[i] != '\0')
  {
    in >> c;
    if (c != exp.expected[i])
    {
      in.setstate(std::ios::failbit);
    }

    i++;
  }

  return in;
}

