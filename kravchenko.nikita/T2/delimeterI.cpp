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

std::istream& kravchenko::operator>>(std::istream& in, AnyCaseDelimeterI&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (std::isalpha(c) && std::isalpha(exp.expected))
  {
    if (std::tolower(c) != std::tolower(exp.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  else if (c != exp.expected)
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
  for (std::size_t i = 0; exp.expected[i] && in; ++i)
  {
    in >> DelimeterI{ exp.expected[i] };
  }
  return in;
}

std::istream& kravchenko::operator>>(std::istream& in, AnyCaseStringDelimeterI&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (std::size_t i = 0; exp.expected[i] && in; ++i)
  {
    in >> AnyCaseDelimeterI{ exp.expected[i] };
  }
  return in;
}
