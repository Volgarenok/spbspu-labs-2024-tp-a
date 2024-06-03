#include "delimiter.hpp"
#include <cctype>
#include <cstring>
#include "streamGuard.hpp"

std::istream& chernikova::operator>>(std::istream& in, ExactSymbolI&& exp)
{
  StreamGuard streamGuard(in);
  in.unsetf(std::ios_base::skipws);
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = in.get();
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, ExactSymbolSavedI&& exp)
{
  StreamGuard streamGuard(in);
  in.unsetf(std::ios_base::skipws);
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  exp.real = in.get();
  if (exp.real != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, AnySymbolI&& exp)
{
  StreamGuard streamGuard(in);
  in.unsetf(std::ios_base::skipws);
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  exp.real = in.get();
  if (!std::strchr(exp.expected, exp.real))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, DelimiterI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  bool isLowerCase = (!exp.upperСase) && (c != exp.expected);
  bool isRightCondition = isLowerCase || (std::tolower(c) != std::tolower(exp.expected));
  if (isRightCondition)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, StringDelimiterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (const char* i = dest.exp; (*i != '\0') && in; ++i)
  {
    in >> DelimiterI{ *i };
  }
  return in;
}
