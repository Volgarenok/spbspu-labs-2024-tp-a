#include "reader.hpp"

#include <string>

#include <streamGuard.hpp>

std::istream& belokurskaya::operator>>(std::istream& in, DelimiterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& belokurskaya::operator>>(std::istream& in, CharI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref;
}

std::istream& belokurskaya::operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterI{ '"' }, dest.ref, '"');
}

std::istream& belokurskaya::operator>>(std::istream& in, StringKeyI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in, dest.ref, ' ');
}

std::istream& belokurskaya::operator>>(std::istream& in, LongLongI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  long long num = 0;
  in >> num;
  if (in)
  {
    dest.num = num;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& belokurskaya::operator>>(std::istream& in, UnsignedLongLongI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  unsigned long long num = 0;
  in >> num;
  if (in)
  {
    dest.num = num;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}
