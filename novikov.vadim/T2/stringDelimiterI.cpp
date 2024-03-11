#include "stringDelimiterI.hpp"
#include "charDelimiterI.hpp"

std::istream& novikov::operator>>(std::istream& in, const StringDelimiterI& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (const char* i = exp.expected; (*i != '\0') && in; ++i)
  {
    using chr_del = CharDelimiterI;
    in >> chr_del{ *i };
  }
  return in;
}

std::istream& novikov::operator>>(std::istream& in, const IgnoreCaseStringDelimiterI& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (const char* i = exp.expected; (*i != '\0') && in; ++i)
  {
    using chr_del = IgnoreCaseCharDelimiterI;
    in >> chr_del{ *i };
  }
  return in;
}