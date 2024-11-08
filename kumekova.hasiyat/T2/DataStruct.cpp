#include <iostream>
#include <algorithm>
#include "DataStruct.hpp"

bool kumekova::DataStruct::operator<(const DataStruct& value) const
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

std::istream& kumekova::operator>>(std::istream& in, kumekova::DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delc = kumekova::DelimiterChar;
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
      in >> KeyHex{ k1 } >> delc{ ':' };
    }
    else if (key == "key2")
    {
      in >> KeyLit{ k2 } >> delc{ ':' };
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

std::ostream& kumekova::operator<<(std::ostream& out, const kumekova::DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  kumekova::iofmtguard fmtguard(out);
  out << "(:key1 " << "0x" << std::uppercase << std::hex << value.key2;
  out << ":key2 " << value.key1 << "ull";
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}

std::istream& kumekova::operator>>(std::istream& in, DelimiterString&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string s = "";
  char c = 0;
  for (size_t i = 0; i < exp.expected.size(); ++i)
  {
    in >> c;
    s += c;
  }
  std::string expUp = exp.expected;
  std::transform(exp.expected.begin(), exp.expected.end(), exp.expected.begin(), ::tolower);
  if (!(s == exp.expected || s == expUp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& kumekova::operator>>(std::istream& in, DelimiterChar&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  kumekova::iofmtguard fmtguard(in);
  char c = 0;
  in >> c;
  if (!(c == exp.expected || c == std::tolower(exp.expected)))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

kumekova::iofmtguard::iofmtguard(std::basic_ios<char>& s) :
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{
}
kumekova::iofmtguard::~iofmtguard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}

std::istream& kumekova::operator>>(std::istream& in, KeyHex&& v)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delc = kumekova::DelimiterChar;
  unsigned long long a = 0;
  kumekova::iofmtguard fmtguard(in);
  in >> delc{ '0' } >> delc{ 'X' } >> std::hex >> a;
  if (in)
  {
    v.value = a;
  }
  return in;
}

std::istream& kumekova::operator>>(std::istream& in, KeyLit&& v)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using dels = kumekova::DelimiterString;
  unsigned long long b = 0;
  in >> b >> dels{ "ULL" };
  if (in)
  {
    v.value = b;
  }
  return in;
}

std::istream& kumekova::operator>>(std::istream& in, KeyString&& v)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delc = kumekova::DelimiterChar;
  std::string s = "";
  in >> delc{ '"' };
  std::getline(in, s, '"');
  if (in)
  {
    v.value = s;
  }
  return in;
}
