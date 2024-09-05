#include "Delimiter.hpp"

#include <istream>
#include <string>
#include <cmath>

std::istream& ayupov::operator>>(std::istream& in, DelimiterChar&& exp)
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
std::istream& ayupov::operator>>(std::istream& in, DelimiterString&& str)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  for (size_t i = 0; i < str.text.size(); i++)
  {
    in >> c;
    if (c != str.text[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
