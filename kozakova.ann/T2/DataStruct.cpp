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

void setKeys(std::istream& in, std::string key, kozakova::DataStruct& value)
{
  using dels = kozakova::DelimiterString;
  using delc = kozakova::DelimiterChar;
  if (key == "key1")
  {
    unsigned long long a = 0;
    in >> a >> dels{ "ULL" };
    if (in)
    {
      value.set_Key1(a);
    }
  }
  else if (key == "key2")
  {
    unsigned long long b = 0;
    kozakova::StreamGuard sguard(in);
    in >> delc{ '0' } >> delc{ 'X' } >> std::hex >> b >> delc{ ':' };
    if (in)
    {
      value.set_Key2(b);
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
      value.set_Key3(s);
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
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
  in >> delc{ '(' } >> delc{ ':' };
  for (int i = 0; i < 3 && in; i++)
  {
    in >> key;
    setKeys(in, key, value);
  }
  in >> delc{ ')' };
  return in;
};

std::ostream& kozakova::operator<<(std::ostream& out, const kozakova::DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  kozakova::StreamGuard sguard(out);
  out << "(:key1 " << value.get_Key1() << "ull";
  out << ":key2 " << "0x" << std::uppercase << std::hex << value.get_Key2();
  out << ":key3 \"" << value.get_Key3() << "\":)";
  return out;
};
