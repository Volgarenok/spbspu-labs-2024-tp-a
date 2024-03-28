#include "DataStruct.h"
#include <iostream>
#include <string>
#include <bitset>
#include <cstring>

petrov::DataStruct::DataStruct(long long key1, unsigned long long key2, const std::string& key3):
  key1_(key1),
  key2_(key2),
  key3_(key3)
{
}
bool petrov::DataStruct::operator<(const DataStruct& other) const
{
  if (!(key1_ == other.key1_))
  {
    return key1_ < other.key1_;
  }
  if (!(key2_ == other.key2_))
  {
    return key2_ < other.key2_;
  }
  return key3_.length() < other.key3_.length();
}
std::ostream& petrov::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  std::string key2Bin = std::bitset<64>(src.key2_).to_string();
  key2Bin.erase(0, key2Bin.find_first_not_of('0'));
  out << "(:key1 " << src.key1_ << "ll:"
    << "key2 0b" << key2Bin << ':'
    << "key3 \"" << src.key3_ << "\":)";
  return out;
}
std::istream& petrov::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input(dest);
  {
    using sep = DelimiterI;
    using label = LabelI;
    in >> sep{ '(' }
      >> sep{ ':' } >> label{ "key" } >> TypeI{ input }
      >> sep{ ':' } >> label{ "key" } >> TypeI{ input }
      >> sep{ ':' } >> label{ "key" } >> TypeI{ input }
    >> sep{ ':' } >> sep{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  else
  {
    in.ignore(')');
    in.setstate(std::ios::goodbit);
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, TypeI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in)
  {
    using sllLit = SignedLongLongLiteralI;
    using ullBin = UnsignedLongLongBinaryI;
    using str = StringI;
    switch (c)
    {
    case '1':
      in >> sllLit{ dest.dataStruct.key1_ };
      break;
    case '2':
      in >> ullBin{ dest.dataStruct.key2_ };
      break;
    case '3':
      in >> str{ dest.dataStruct.key3_ };
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
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
  char c = '0';
  in.get(c);
  if (in && (c != '\"'))
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    std::getline(in, dest.ref, '\"');
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, DelimiterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in.get(c);
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
  char data[4] = "";
  in.read(data, 3);
  data[3] = '\0';
  if (in && (data != dest.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

