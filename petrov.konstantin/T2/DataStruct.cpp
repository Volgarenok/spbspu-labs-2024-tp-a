#include "DataStruct.h"
#include <iostream>
#include <string>
#include <bitset>
#include <cstring>

bool petrov::operator<(const DataStruct& left, const DataStruct& right)
{
  if (!(left.key1 == right.key1))
  {
    return left.key1 < right.key1;
  }
  if (!(left.key2 == right.key2))
  {
    return left.key2 < right.key2;
  }
  return left.key3.length() < right.key3.length();
}
std::ostream& petrov::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  std::string key2Bin = "";
  if (src.key2 != 0)
  {
    key2Bin = std::bitset<64>(src.key2).to_string();
    key2Bin.erase(0, key2Bin.find_first_not_of('0'));
  }
  out << "(:key1 " << src.key1 << "ll:"
    << "key2 0b0" << key2Bin << ':'
    << "key3 \"" << src.key3 << "\":)";
  return out;
}
std::istream& petrov::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterI;
    using label = LabelI;
    using sllLit = SignedLongLongLiteralI;
    using ullBin = UnsignedLongLongBinaryI;
    using str = StringI;
    in >> sep{ '(' } >> sep{ ':' };
    std::string key = "";
    for (size_t i = 0; i < 3; ++i)
    {
      in >> key;
      if (key == "key1")
      {
        in >> sllLit{ dest.key1 };
      }
      else if (key == "key2")
      {
        in >> ullBin{ dest.key2 };
      }
      else if (key == "key3")
      {
        in >> str{ dest.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
      in >> sep{ ':' };
    }
    in >> sep{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, SignedLongLongLiteralI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> dest.ref;
  char suffix[3] = "";
  in.read(suffix, 2);
  suffix[2] = '\0';
  if (in && std::strcmp(suffix, "ll") && (std::strcmp(suffix, "LL")))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, UnsignedLongLongBinaryI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterI{ '0' };
  char c = '0';
  in.get(c);
  if (in && (c != 'b') && (c != 'B'))
  {
    in.setstate(std::ios::failbit);
  }
  else if (in)
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
  return std::getline(in >> DelimiterI{ '"' }, dest.ref, '"');
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
std::istream& petrov::operator>>(std::istream& in, LabelI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  if ((in >> data) && (data != dest.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
