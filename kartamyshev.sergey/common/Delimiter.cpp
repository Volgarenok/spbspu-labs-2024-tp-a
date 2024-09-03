#include "Delimiter.h"

std::istream& kartamyshev::operator>>(std::istream& in, DelimiterSym&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  in >> c;

  if (std::tolower(c) != std::tolower(exp.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& kartamyshev::operator>>(std::istream& in, DelimiterStr&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  for (size_t i = 0; exp.expected[i] != '\0'; i++)
  {
    in >> DelimiterSym{ exp.expected[i] };
  }
  return in;
}
