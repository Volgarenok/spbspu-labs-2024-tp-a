#include "delimeter.hpp"

std::istream& piyavkin::operator>>(std::istream& in, DelimeterChar&& exp)
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

std::istream& piyavkin::operator>>(std::istream& in, DelimeterString&& exp)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    std::string c = "";
    in >> c;
    if (c != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}