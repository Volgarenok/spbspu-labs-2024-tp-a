#include "FormatUtils.h"
#include <iostream>
#include <string>
#include <bitset>

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
    char binary[65]{};
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
// std::string petrov::toBinary(unsigned long long src)
// {
//   std::string binary = "";
//   if (src)
//   {
//     binary = std::bitset<64>(src).to_string();
//     binary.erase(0, binary.find_first_not_of('0'));
//   }
//   return '0' + binary;
// }
