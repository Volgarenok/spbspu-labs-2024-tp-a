#include "delimeters.hpp"
#include "stream_guard.hpp"

std::istream & namestnikov::operator>>(std::istream & in, DelimeterChar && del)
{
  std::istream::sentry guard(in);
  StreamGuard streamGuard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  c = std::tolower(c);
  if (c != del.delimeter)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & namestnikov::operator>>(std::istream & in, DelimeterString && del)
{
  std::istream::sentry guard(in);
  StreamGuard streamGuard(in);
  if (!guard)
  {
    return in;
  }
  size_t i = 0;
  while (del.delimeter[i] != '\0')
  {
    in >> DelimeterChar{del.delimeter[i]};
    ++i;
  }
  return in;
}
