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
  c = std::tolower(c);

  if (in && (c != exp.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& spiridonov::operator>>(std::istream& in, UllLiteralIO&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> exp.expected >> DelimeterChar{ 'u' } >> DelimeterChar{ 'l' } >> DelimeterChar{ 'l' };
}

std::istream& spiridonov::operator>>(std::istream& in, DelimeterString&& str)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  for (size_t i = 0; i < str.expected.size(); i++)
  {
    in >> c;
    if (c != str.expected[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
