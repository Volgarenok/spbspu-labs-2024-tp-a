#include "dataStruct.hpp"
#include "wrappers.hpp"
#include <delimeters.hpp>
#include <scopeGuard.hpp>

bool ravinskij::DataStruct::operator<(const DataStruct& rhs) const
{
  if (key1 == rhs.key1)
  {
    if (key2 == rhs.key2)
    {
      return key3.size() < rhs.key3.size();
    }
    return key2 < rhs.key2;
  }
  return key1 < rhs.key1;
}

std::istream& ravinskij::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  const size_t KEYS_COUNT = 3;
  DataStruct temp{0, 0, ""};
  using del = CharDelimeter;
  in >> del{'('};
  for (size_t i = 0; i < KEYS_COUNT; ++i)
  {
    char order = 0;
    in >> del{':'} >> del{'k'} >> del{'e'} >> del{'y'} >> order;
    if (!in)
    {
      break;
    }

    if (order == '1')
    {
      in >> BinUll{temp.key1};
    }
    else if (order == '2')
    {
      in >> HexUll{temp.key2};
    }
    else if (order == '3')
    {
      in >> StrKey{temp.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }

  in >> del{':'} >> del{')'};
  if (in)
  {
    data = temp;
  }

  return in;
}

std::ostream& ravinskij::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << ":key1 0b" << (data.key1 == 0 ? "" : "0") << data.key1;
  out << ":key2 0x" << std::hex << std::uppercase << data.key2;
  out << ":key3 \"" << data.key3 << '"' << ":)";
  return out;
}

