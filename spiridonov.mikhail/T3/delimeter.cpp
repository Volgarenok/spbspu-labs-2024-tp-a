#include "delimeter.hpp"

std::istream& spiridonov::operator>>(std::istream& in, DelimeterChar&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (isalpha(c))
  {
    c = tolower(c);
  }
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& spiridonov::operator>>(std::istream& in, DelimeterString&& exp)
{
  size_t i = 0;
  while (exp.expected[i] != '\0')
  {
    in >> DelimeterChar{ exp.expected[i++] };
  }
  return in;
}
