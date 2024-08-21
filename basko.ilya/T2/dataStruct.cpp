#include "dataStruct.hpp"
#include <iomanip>
#include <complex>
#include <string>
#include "delimiters.hpp"
#include "scopeGuard.hpp"
#include "inputKey.hpp"

std::istream& basko::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  ScopeGuard scopeGuard(in);
  size_t keyNumber = 0;
  using delChar = DelimiterChar;
  using delString = DelimiterString;
  in >> delChar({ '(' });
  for (size_t i = 0; i < 3; ++i)
  {
    in >> delString({ ":key" }) >> keyNumber;
    if (keyNumber == 1)
    {
      in >> UllHexKey{ value.key1 };
    }
    else if (keyNumber == 2)
    {
      in >> CmpLspKey{ value.key2 };
    }
    else if (keyNumber == 3)
    {
      in >> StringKey{ value.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> delString({ ":)" });
  return in;
}

std::ostream& basko::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  ScopeGuard scopeGuard(out);
  out << std::setprecision(1) << std::fixed;
  out << "(:" << "key1 " << "0x" << std::uppercase << std::hex << data.key1;
  out << ":key2 " << "#c(" << data.key2.real() << ' ' << data.key2.imag() << "):";
  out << "key3 " << '"' << data.key3 << '"' << ":)";
  return out;
}

bool basko::DataStruct::operator<(const DataStruct& data) const
{
  if (key1 == data.key1)
  {
    if (std::abs(key2) == std::abs(data.key2))
    {
      return key3.length() < data.key3.length();
    }
    return std::abs(key2) < std::abs(data.key2);
  }
  return key1 < data.key1;
}
