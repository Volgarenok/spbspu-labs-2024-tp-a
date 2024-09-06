#include "delimiter.hpp"

std::istream& zhakha::operator>>(std::istream& in, DelimiterChar&& exp)
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

std::istream& zhakha::operator>>(std::istream& in, DelimiterIsAlpha&& exp)
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

std::istream& zhakha::operator>>(std::istream& in, DelimiterString&& exp)
{
  size_t i = 0;
  while (exp.expected[i] != '\0')
  {
    if (std::isalpha(exp.expected[i]))
    {
      in >> DelimiterIsAlpha{ exp.expected[i++] };
    }
    else
    {
      in >> DelimiterChar{ exp.expected[i++] };
    }
  }
  return in;
}