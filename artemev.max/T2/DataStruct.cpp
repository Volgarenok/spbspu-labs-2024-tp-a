#include "DataStruct.hpp"
#include <bitset>
#include <algorithm>
#include <Delimiter.hpp>
#include <ScopeGuard.hpp>

std::string getBinNumber(unsigned long long value)
{
  std::bitset< 64 > bin(value);
  std::string binString = bin.to_string();
  return "0" + binString.erase(0, binString.find('1'));
}

bool artemev::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }

  else if (key2 != other.key2)
  {
    return key2 < other.key2;
  }

  return (key3.length() <= other.key3.length());
}

std::istream& artemev::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  ScopeGuard scopeGuard(in);

  using delChar = DelimiterCharI;
  using delString = DelimiterStringI;

  const size_t KEY_NUMBER = 3;
  size_t keyI = 0;

  in >> delChar{ '(' };

  for (size_t i = 0; i < KEY_NUMBER; ++i)
  {
    in >> delString{ ":key" } >> keyI;
    switch (keyI)
    {
      case 1:
      {
        in >> value.key1 >> delChar{ 'd' };
        break;
      }
      case 2:
      {
        std::bitset< 64 > bin;
        in >> delString{ "0b" } >> bin;
        if (in)
        {
          value.key2 = bin.to_ullong();
        }
        break;
      }
      case 3:
      {
        in >> delChar{ '"' };
        std::getline(in, value.key3, '"');
        break;
      }
      default:
      {
        in.setstate(std::ios::failbit);
      }
    }
  }

  in >> delString{ ":)" };
  return in;
}

std::ostream& artemev::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  ScopeGuard scopeGuard(out);

  out << std::setprecision(1) << std::fixed << "(";
  out << ":key1 " << value.key1 << "d";
  out << ":key2 0b" << getBinNumber(value.key2);
  out << ":key3 \"" << value.key3 << "\":)";

  return out;
}
