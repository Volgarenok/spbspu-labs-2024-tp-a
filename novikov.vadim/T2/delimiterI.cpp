#include "delimiterI.hpp"

std::istream& novikov::operator>>(std::istream& in, const DelimiterI& exp)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    char ch = '\0';
    in >> ch;
    if (ch != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}