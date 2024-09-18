#include "delimiter.hpp"
#include <istream>
#include "stream_guard.hpp"

std::istream& zaitsev::operator>>(std::istream& in, const Delimiter&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t i = 0;
  while (in && exp.expected[i])
  {
    char c = 0;
    in >> c;
    if (c == ' ')
    {
      continue;
    }
    if (c == '\n')
    {
      in.setstate(std::ios::badbit);
      return in;
    }
    if (std::tolower(c) != std::tolower(exp.expected[i++]))
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
