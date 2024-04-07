#include "FormatUtils.h"
#include <iostream>
#include <string>

std::istream& petrov::operator>>(std::istream& in, SignedLongLongLiteralI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> dest.ref;
  in >> DelimiterI{ 'l' } >> DelimiterI{ 'l' };
  return in;
}
std::istream& petrov::operator>>(std::istream& in, UnsignedLongLongBinaryI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterI{ '0' } >> DelimiterI{ 'b' };
  if (in)
  {
    char binary[64] = "";
    in.get(binary, 64, ':');
    for (size_t i = 0; binary[i] != '\0'; ++i)
    {
      if (!std::isdigit(binary[i]))
      {
        in.setstate(std::ios::failbit);
        return in;
      }
    }
    dest.ref = std::stoull(binary, nullptr, 2);
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterI{ '\"' }, dest.ref, '\"');
}
std::istream& petrov::operator>>(std::istream& in, DelimiterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
