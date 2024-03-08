#include "delimeterI.hpp"

std::istream& kravchenko::operator>>(std::istream& in, DelimeterI&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
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

std::istream& kravchenko::operator>>(std::istream& in, StringDelimeterI&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < exp.expected.size() && in; ++i)
  {
    in >> DelimeterI{ exp.expected[i] };
  }
  return in;
}
