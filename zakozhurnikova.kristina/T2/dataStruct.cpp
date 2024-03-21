#include "dataStruct.hpp"
#include <iomanip>
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
  char keyNumber = 0;

  in >> delCh{'('};
  for (size_t i = 0; i < NUMBER_OF_KEYS; ++i)
  {
    in >> delSt{":key"} >> keyNumber;
    if (keyNumber == '1')
    {
      in >> key1 >> delCh{'d'};
    }
    else if (keyNumber == '2')
    {
      ScopeGuard guard(in);
      in >> delCh{ '0' } >> delCh{ 'x' } >> std::hex >> key2;
    }
    else if (keyNumber == '3')
    {
      in >> delCh{ '"' };
      std::getline(in, key3, '"');
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  if (in)
  {
    data = DataStruct(key1, key2, key3);
  }
  in >> delSt{":)"};
  return in;
}

std::ostream& zakozhurnikova::operator<<(std::ostream& out, const zakozhurnikova::DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  ScopeGuard scopeGuard(out);

  out << std::fixed << std::setprecision(1) << "(:key1 " << data.key1 << "d";
  out << std::hex << std::uppercase << ":key2 " << "0x" << data.key2;
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
};
