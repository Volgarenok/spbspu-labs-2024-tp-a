#include "delimeter.hpp"

std::istream& piyavkin::operator>>(std::istream& in, Delimeter&& exp)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char c = 0;
    in >> c;
    if (c != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}