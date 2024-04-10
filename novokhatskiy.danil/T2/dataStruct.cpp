#include "dataStruct.hpp"
#include <iostream>
#include <bitset>
#include "delimiter.hpp"
#include "inputKeys.hpp"

bool novokhatskiy::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (key2.first * other.key2.second == other.key2.first * key2.second)
    {
      return key3.size() < other.key3.size();
    }
    return key2.first * other.key2.second < other.key2.first * key2.second;
  }
  return key1 < other.key1;
}

std::istream& novokhatskiy::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t currKey = 0;
  DataStruct tmp = { 0, { 0, 0 }, "" };
  constexpr size_t maxNumberOfKeys = 3;
  in >> strictDel{ '(' };
  for (size_t i = 0; i < maxNumberOfKeys && in; ++i)
  {
    in >> strictStrD{ ":key" } >> currKey;

    if (currKey == 1)
    {
      in >> BinKey{ tmp.key1 };
    }

    else if (currKey == 2)
    {
      in >> RATKey{ tmp.key2 };
    }

    else if (currKey == 3)
    {
      in >> STRKey{ tmp.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> strictStrD{ ":)" };

  if (in)
  {
    data = tmp;
  }
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:key1 " << "0b" << (data.key1 == 0 ? "" : "0") << data.key1;
  out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
  out << ":key3 " << '"' << data.key3 << '"' << ":)";
  return out;
}
