#include "format.hpp"
#include <iostream>
#include "delimiter.hpp"

std::istream & erohin::operator>>(std::istream & input, DoubleFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  long long integer = 0;
  double fractional = 0.0;
  input >> integer >> fractional >> IgnoredCaseDelimiter{ 'd' };
  if (input)
  {
    dest.ref = integer + fractional * (integer >= 0 ? 1 : -1);
  }
  return input;
}

std::istream & erohin::operator>>(std::istream & input, LongLongFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return input >> dest.ref >> IgnoredCaseDelimiter{ 'l' } >> IgnoredCaseDelimiter{ 'l' };
}

std::istream & erohin::operator>>(std::istream & input, StringFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return std::getline(input >> SensetiveCaseDelimiter{ '"' }, dest.ref, '"');
}
