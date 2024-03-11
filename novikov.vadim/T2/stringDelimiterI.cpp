#include "stringDelimiterI.hpp"
#include <cctype>
#include "charDelimiterI.hpp"

std::istream& novikov::operator>>(std::istream& in, const StringDelimiterI& exp)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    for (const char* i = exp.expected; (*i != '\0') && in; ++i)
    {
      using chr_del = CharDelimiterI;
      in >> chr_del{ *i, exp.ignore_case };
    }
  }
  return in;
}
