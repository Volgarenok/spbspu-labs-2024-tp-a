#include "delimiterI.hpp"

std::istream& novikov::operator>>(std::istream& in, const CharDelimiterI& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char ch{};
  in >> ch;
  if (exp.ignore_case)
  {
    if (std::isalpha(ch) && std::isalpha(exp.expected))
    {
      if (std::tolower(ch) != std::tolower(exp.expected))
      {
        in.setstate(std::ios::failbit);
      }
    }
    else if (ch != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  else
  {
    if (ch != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

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
    in >> chr_del{ *i, exp.ignore_case };
  }
  return in;
}