#include "DataStruct.hpp"
#include <iostream>
#include "Delimiters.hpp"
#include "StreamGuard.hpp"

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
  using dels = kozakova::DelimiterString;
  std::string key = "";
  in >> delc{ '(' } >> delc{ ':' };
  for (int i = 0; i < 3 && in; i++)
  {
    in >> key;
    if (key == "key1")
    {
      unsigned long long a = 0;
      in >> a >> dels{ "ULL" };
      if (in)
      {
        value.key1 = a;
      }
    }
    else if (key == "key2")
    {
      unsigned long long b = 0;
      kozakova::StreamGuard sguard(in);
      in >> delc{ '0' } >> delc{ 'X' } >> std::hex >> b >> delc{ ':' };
      if (in)
      {
        value.key2 = b;
      }
    }
    else if (key == "key3")
    {
      std::string s = "";
      in >> delc{ '"' };
      std::getline(in, s, '"');
      in >> delc{ ':' };
      if (in)
      {
        value.key3 = s;
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> delc{ ')' };
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
