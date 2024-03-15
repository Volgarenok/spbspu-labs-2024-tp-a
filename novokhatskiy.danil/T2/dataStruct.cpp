#include "dataStruct.hpp"
#include <bitset>
#include "delimiter.hpp"
#include "parseKeys.hpp"

bool novokhatskiy::DataStruct::operator<(const DataStruct &other) const
{
  if (key1 == other.key1)
  {
    if (key2.first * other.key2.second == key2.second * other.key2.first)
    {
      return key3.size() < other.key3.size();
    }
    return key2.first * other.key2.second < key2.second * other.key2.first;
  }
  return key1 < other.key1;
}

std::istream &novokhatskiy::operator>>(std::istream &in, DataStruct &data)
{
  using strD = novokhatskiy::DelimiterString;
  using charD = novokhatskiy::Delimiter;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  constexpr size_t maxKeys = 3;
  in >> charD{'('};
  DataStruct res = {0, {0, 0}, ""};
  for (size_t i = 0; i < maxKeys && in; ++i)
  {
    char key = 0;
    in >> strD{":key"} >> key;
    switch (key)
    {
    case '1':
      in >> UnsignedLLKey{res.key1};
      break;
    case '2':
      in >> PairKey{res.key2};
      break;
    case '3':
      in >> StringKey{res.key3};
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
    in >> strD{":)"};
    if (in)
    {
      data = res;
    }
  }
  return in;
}

std::ostream &novokhatskiy::operator<<(std::ostream &out, const DataStruct &data)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << "(:key1 "
        << "0b" << std::bitset<64>(data.key1);
    out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
    out << ":key3 " << '"' << data.key3 << '"' << ":)";
  }
  return out;
}

void novokhatskiy::inputKeys(std::istream &in, size_t &numberKey, DataStruct &data)
{
  using strAD = novokhatskiy::DelimiterAlphaString;
  using strD = novokhatskiy::DelimiterString;
  if (numberKey == 1)
  {
    unsigned long long tmp = 0;
    in >> strAD{"0b"} >> tmp;
    if (in)
    {
      data.key1 = tmp;
    }
  }
  else if (numberKey == 2)
  {
    long long ll = 0;
    unsigned long long ull = 0;
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
    in >> str;
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
