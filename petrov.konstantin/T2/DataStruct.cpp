#include "DataStruct.h"
#include <iostream>
#include <string>
#include <bitset>
#include <cstring>
#include "FormatUtils.h"

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
    using sep = petrov::DelimiterI;
    using sllLit = petrov::SignedLongLongLiteralI;
    using ullBin = petrov::UnsignedLongLongBinaryI;
    using str = petrov::StringI;
    in >> sep{ '(' } >> sep{ ':' };
    std::string key = "";
    for (size_t i = 0; i < 3; ++i)
    {
      in >> key;
      if (key == "key1")
      {
        in >> sllLit{ input.key1 };
      }
      else if (key == "key2")
      {
        in >> ullBin{ input.key2 };
      }
      else if (key == "key3")
      {
        in >> str{ input.key3 };
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
