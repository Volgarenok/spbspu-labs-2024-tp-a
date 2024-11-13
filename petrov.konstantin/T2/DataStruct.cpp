#include "DataStruct.h"
#include <iostream>
#include <string>
#include "FormatUtils.h"
#include "Delimiter.h"

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
  using ullBinO = petrov::UnsignedLongLongBinaryO;
  out << "(:key1 " << src.key1 << "ll:";
  out << "key2 0b" << ullBinO{ src.key2 } << ':';
  out << "key3 \"" << src.key3 << "\":)";
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
    using del = petrov::DelimiterI;
    using sllLit = petrov::SignedLongLongLiteralI;
    using ullBinI = petrov::UnsignedLongLongBinaryI;
    using str = petrov::StringI;
    in >> del{ '(' } >> del{ ':' };
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
        in >> ullBinI{ input.key2 };
      }
      else if (key == "key3")
      {
        in >> str{ input.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
      in >> del{ ':' };
    }
    in >> del{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}
