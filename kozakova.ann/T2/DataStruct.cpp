#include "DataStruct.hpp"
#include <iostream>
#include "Delimiters.hpp"
#include "StreamGuard.hpp"
#include "KeysIn.hpp"

bool kozakova::DataStruct::operator<(const DataStruct& value) const
{
  if (key1 != value.key1)
  {
    return key1 < value.key1;
  }
  if (key2 != value.key2)
  {
    return key2 < value.key2;
  }
  return key3.size() < value.key3.size();
}

std::istream& kozakova::operator>>(std::istream& in, kozakova::DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delc = kozakova::DelimiterChar;
  std::string key = "";
  unsigned long long k1 = 0;
  unsigned long long k2 = 0;
  std::string k3 = "";
  in >> delc{ '(' } >> delc{ ':' };
  for (int i = 0; i < 3 && in; i++)
  {
    in >> key;
    if (key == "key1")
    {
      in >> KeyUll{ k1 } >> delc{ ':' };
    }
    else if (key == "key2")
    {
      in >> KeyHex{ k2 } >> delc{ ':' };
    }
    else if (key == "key3")
    {
      in >> KeyString{ k3 } >> delc{ ':' };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> delc{ ')' };
  if (in)
  {
    value = DataStruct{ k1,k2,k3 };
  }
  return in;
}

std::ostream& kozakova::operator<<(std::ostream& out, const kozakova::DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  kozakova::StreamGuard sguard(out);
  out << "(:key1 " << value.key1 << "ull";
  out << ":key2 " << "0x" << std::uppercase << std::hex << value.key2;
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}
