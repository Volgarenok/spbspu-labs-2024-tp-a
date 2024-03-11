#include "dataStruct.hpp"
#include <bitset>
#include "delimiter.hpp"

bool novokhatskiy::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (key2.first + key2.second == other.key2.first + other.key2.second)
    {
      return key3 < other.key3;
    }
    return key2.first + key2.second < other.key2.first + other.key2.second;
  }
  return key1 < other.key1;
}

bool novokhatskiy::DataStruct::operator>(const DataStruct& other) const
{
  return !(*this < other);
}

bool novokhatskiy::DataStruct::operator<=(const DataStruct& other) const
{
  return !(other < *this);
}

bool novokhatskiy::DataStruct::operator>=(const DataStruct& other) const
{
  return !(*this < other);
}

bool novokhatskiy::DataStruct::operator==(const DataStruct& other) const
{
  return !(other < *this) && !(*this < other);
}

bool novokhatskiy::DataStruct::operator!=(const DataStruct& other) const
{
  return !(*this == other);
}

std::istream& novokhatskiy::operator>>(std::istream& in, novokhatskiy::DataStruct& data)
{
  using strD = novokhatskiy::DelimiterString;
  using charD = novokhatskiy::Delimiter;
  std::istream::sentry sentry(in);
  if (sentry)
  {
    size_t currKey{};
    const size_t maxNumberOfKeys = 3;
    in >> charD{ '(' };
    for (size_t i = 0; i < maxNumberOfKeys; i++)
    {
      in >> strD{ ":key" } >> currKey;
      novokhatskiy::inputKeys(in, currKey, data);
    }
    in >> strD{ ":)" };
  }
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const novokhatskiy::DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    std::bitset< 64 > key1(data.key1);
    out << "(:key1 " << "0b" << key1;
    out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
    out << ":key3 " << '"' << data.key3 << '"' << ":)";
  }
  return out;
}

void novokhatskiy::inputKeys(std::istream& in, size_t numberKey, novokhatskiy::DataStruct& data)
{
  using strD = novokhatskiy::DelimiterString;
  if (numberKey == 1)
  {
    unsigned long long tmp{};
    in >> strD{"0b"} >> tmp;
    if (in)
    {
      data.key1 = tmp;
    }
  }
  else if (numberKey == 2)
  {
    long long ll{};
    unsigned long long ull{};
    in >> strD{ "(:N" } >> ll >> strD{ ":D" } >> ull >> strD{ ":)" };
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
