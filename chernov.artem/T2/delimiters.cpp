#include "delimiters.hpp"
#include "streamGuard.hpp"
#include <iostream>
#include <cmath>

std::istream& chernov::operator>>(std::istream& in, UnsignedLongLongIO&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> DelimiterIO{'0'} >> DelimiterIO{'x'} >> std::hex >> exp.value_;
}

std::istream& chernov::operator>>(std::istream& in, DelimiterIO&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> exp.value_;
}

std::istream& chernov::operator>>(std::istream& in, DoubleIO&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> std::scientific >> exp.value_;
}

std::istream& chernov::operator>>(std::istream& in, StringIO&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  chernov::StreamGuard guard(in);
  return in >> DelimiterIO{'"'} >> exp.value_ >> DelimiterIO{'"'};
}

std::istream& chernov::operator>>(std::istream& in, DelimiterStringIO&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < exp.string_.length(); i++)
  {
    in >> DelimiterIO{exp.string_[i]};
  }
  return in;
}
