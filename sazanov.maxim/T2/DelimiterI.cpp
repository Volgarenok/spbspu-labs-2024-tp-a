#include "DelimiterI.hpp"
#include <iostream>

std::istream& sazanov::operator>>(std::istream& in, DelimiterI&& exp)
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

std::istream& sazanov::operator>>(std::istream& in, VariableDelimiterI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if ((c != exp.firstExpected) && (c != toupper(exp.secondExpected)))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& sazanov::operator>>(std::istream& in, StringDelimiterI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  for (char expChar : exp.expected)
  {
    in >> DelimiterI{expChar};
  }
  return in;
}
