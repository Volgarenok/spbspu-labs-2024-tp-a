#if defined(_WIN32)
#define strcasecmp _stricmp
#endif
#include "delimiter.hpp"
#include <istream>
#include <cstring>

std::istream& zaitsev::operator>>(std::istream& in, const CharDelimiter&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& zaitsev::operator>>(std::istream& in, const StrDelimiter&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t exp_len = std::strlen(exp.expected) + 1;
  char* buff = new char[exp_len];
  buff[exp_len - 1] = '\0';
  for (size_t i = 0; i < exp_len - 1; ++i)
  {
    in >> buff[i];
  }
  if (strcasecmp(buff, exp.expected))
  {
    in.setstate(std::ios::failbit);
  }
  delete[] buff;
  return in;
}
