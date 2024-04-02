#include "dataStruct.hpp"
#include <iomanip>
#include "delimiter.hpp"
#include "scopeGuard.hpp"
#include "tokens.hpp"

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
      in >> DblLit{key1};
    }
    else if (keyNumber == '2')
    {
      in >> UllHex{key2};
    }
    else if (keyNumber == '3')
    {
      in >> StringKey{key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  if (in)
  {
    data = DataStruct{key1, key2, key3};
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
