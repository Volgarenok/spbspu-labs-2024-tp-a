#include "delimeter.hpp"

std::istream& piyavkin::operator>>(std::istream& in, DelimeterChar&& exp)
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

std::istream& piyavkin::operator>>(std::istream& in, DelimeterAlphaChar&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  c = std::tolower(c);
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& piyavkin::operator>>(std::istream& in, DelimeterString&& exp)
{
  size_t i = 0;
  while (exp.expected[i] != '\0')
  {
    if (std::isalpha(exp.expected[i]))
    {
      in >> DelimeterAlphaChar{exp.expected[i++]};
    }
    else
    {
      in >> DelimeterChar{exp.expected[i++]};
    }
  }
  return in;
}
