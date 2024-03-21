#include "dataStruct.hpp"
#include <bitset>
#include <iostream>
#include "delimiter.hpp"

bool novokhatskiy::DataStruct::operator<(const DataStruct &other) const
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

std::istream &novokhatskiy::operator>>(std::istream &in, DataStruct &data)
{
  using strD = novokhatskiy::DelimiterString;
  using charD = novokhatskiy::Delimiter;
  std::istream::sentry sentry(in);
  if (sentry)
  {
    size_t currKey = 0;
    constexpr size_t maxNumberOfKeys = 3;
    in >> charD{'('};
    for (size_t i = 0; i < maxNumberOfKeys && in; ++i)
    {
      in >> strD{":key"} >> currKey;
      novokhatskiy::inputKeys(in, currKey, data);
    }
    in >> strD{":)"};
  }
  return in;
}

std::ostream &novokhatskiy::operator<<(std::ostream &out, const DataStruct &data)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << "(:key1 " << "0b" << novokhatskiy::convertToBit(data.key1);
    out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
    out << ":key3 " << '"' << data.key3 << '"' << ":)";
  }
  return out;
}

void novokhatskiy::inputKeys(std::istream &in, size_t &numberKey, DataStruct &data)
{
  using strD = novokhatskiy::DelimiterString;
  using strAD = novokhatskiy::DelimiterAlphaString;
  if (numberKey == 1)
  {
    std::bitset<64> bin;
    in >> strAD{"0b"} >> bin;
    if (in)
    {
      data.key1 = bin.to_ullong();
    }
  }
  else if (numberKey == 2)
  {
    long long ll{};
    unsigned long long ull{};
    in >> strAD{"(:n"} >> ll >> strAD{":d"} >> ull >> strD{":)"};
    if (in)
    {
      data.key2.first = ll;
      data.key2.second = ull;
    }
  }
  else if (numberKey == 3)
  {
    std::string str = "";
    in >> Delimiter{'"'};
    std::getline(in, str, '"');
    if (in)
    {
      data.key3 = str;
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
}

std::string novokhatskiy::convertToBit(unsigned long long value)
{
  std::bitset<64> bit(value);
  std::string strBit = bit.to_string();
  if (strBit[0] != '1')
  {
    strBit.erase(1, strBit.find_first_not_of('0', 1) - 1);
  }
  return strBit;
}
