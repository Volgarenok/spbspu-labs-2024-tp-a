#include "Delimiter.hpp"

#include <iostream>
#include <ios>

std::istream& artemev::operator>>(std::istream& in, const Delimiter&& delimiter)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    char c = 0;
    in >> c;
    if (c != delimiter.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
