#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "scopeGuard.hpp"

zakozhurnikova::DataStruct::DataStruct():
  key1(0.0),
  key2(0),
  key3("")
{}

zakozhurnikova::DataStruct::DataStruct(double keyOne, unsigned long long keyTwo, std::string keyThree):
  key1(keyOne),
  key2(keyTwo),
  key3(keyThree)
{}

bool zakozhurnikova::DataStruct::operator<(const DataStruct& rhs) const
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

bool zakozhurnikova::DataStruct::operator>(const DataStruct& rhs) const
{
  return rhs < *this;
}

bool zakozhurnikova::DataStruct::operator<=(const DataStruct& rhs) const
{
  return !(*this > rhs);
}

bool zakozhurnikova::DataStruct::operator>=(const DataStruct& rhs) const
{
  return !(*this < rhs);
}

bool zakozhurnikova::DataStruct::operator==(const DataStruct& rhs) const
{
  return !(*this < rhs) && !(*this > rhs);
}

bool zakozhurnikova::DataStruct::operator!=(const DataStruct& rhs) const
{
  return !(*this == rhs);
}

std::istream& zakozhurnikova::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  ScopeGuard scopeGuard(in);
  using delCh = DelimiterChar;
  using delSt = DelimiterString;
  using ull = unsigned long long;

  double key1 = 0.0;
  ull key2 = 0;
  std::string key3 = "";
  const size_t NUMBER_OF_KEYS = 3;
  size_t keyNumber = 0;

  in >> delCh{'('} >> delCh{':'};
  for (size_t i = 0; i < NUMBER_OF_KEYS; ++i)
  {
    in >> delSt{"key"} >> keyNumber;
    if (keyNumber == 1)
    {
    }
    else if (keyNumber == 2)
    {
    }
    else if (keyNumber == 3)
    {
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> delCh{':'};
  }
  if (in)
  {
    data = DataStruct(key1, key2, key3);
  }
  in >> delSt{")"};
  return in;
}
