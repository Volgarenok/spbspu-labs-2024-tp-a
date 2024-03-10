#include "stringDelimiterI.hpp"

std::istream& novikov::operator>>(std::istream& in, const StringDelimiterI& exp)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    bool success = true;
    for (const char* i = exp.expected; (*i != '\0') && success; ++i)
    {
      char ch = '\0';
      in >> ch;
      bool error_ignore = ignore_case && (ch != std::tolower(*i));
      bool error_no_ignore = !ignore_case && (ch != *i);
      if (error_ignore || error_no_ignore)
      {
        in.setstate(std::ios::failbit);
        success = false;
      }
    }
  }
  return in;
}
