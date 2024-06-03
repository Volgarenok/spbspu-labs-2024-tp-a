#include "FormatUtils.h"
#include <iostream>
#include <string>
#include <bitset>
#include "Delimiter.hpp"

std::ostream& petrov::operator<<(std::ostream& out, const UnsignedLongLongBinaryO&& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  std::string binary = "";
  if (src.val)
  {
    binary = std::bitset< 64 >(src.val).to_string();
    binary.erase(0, binary.find_first_not_of('0'));
  }
  return out << ('0' + binary);
}
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
    char binary[64]{};
    for (size_t i = 0; std::isdigit(in.peek()); ++i)
    {
      in.get(binary[i]);
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
