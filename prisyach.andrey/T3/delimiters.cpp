#include "delimiters.hpp"
#include "streamguard.hpp"

std::istream & prisyach::operator>>(std::istream & in, DelimiterChar && del)
{
  std::istream::sentry guard(in);
  StreamGuard streamGuard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    char c = 0;
    in >> c;
    c = std::tolower(c);
    if (c != del.delimeter)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}

std::istream & prisyach::operator>>(std::istream & in, DelimiterString && del)
{
  std::istream::sentry guard(in);
  StreamGuard streamGuard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    size_t i = 0;
    while (del.delimeter[i] != '\0')
    {
      in >> DelimiterChar{del.delimeter[i]};
      ++i;
    }
    return in;
  }
}
