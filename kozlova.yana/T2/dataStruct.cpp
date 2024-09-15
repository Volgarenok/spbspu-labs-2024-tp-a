#include "dataStruct.hpp"
#include <iomanip>
#include "value.hpp"
#include <delimiter.hpp>
#include "scopeGuard.hpp"

bool kozlova::DataStruct::operator<(const DataStruct & dest) const
{
  if (key1 == dest.key1)
  {
    if (key2 == dest.key2)
    {
      return key3.size() < dest.key3.size();
    }
    return key2 < dest.key2;
  }
  return key1 < dest.key1;
}

std::istream & kozlova::operator>>(std::istream & in, DataStruct & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delC = DelimiterCharIO;
  using delS = DelimiterStringIO;
  using dbl = DblLitIO;
  using str = StringIO;
  using ratF = RatLspFIO;
  using ratS = RatLspSIO;

  double key1 = 0.0;
  long long firstKey2 = 0;
  unsigned long long secondKey2 = 0;
  std::pair< long long, unsigned long long > key2(0, 0);
  std::string key3 = "";
  char valueKey = 0;

  in >> delC{ '(' };
  for (size_t i = 0; i < 3; ++i)
  {
    in >> delS{ ":key" } >> valueKey;
    switch (valueKey)
    {
    case '1':
      in >> dbl{ key1 };
      break;
    case '2':
      in >> delS{ "(:N" } >> ratF{ firstKey2 };
      key2.first = firstKey2;
      in >> delS{ ":D" } >> ratS{ secondKey2 };
      key2.second = secondKey2;
      in >> delS{ ":)" };
      break;
    case '3':
      in >> str{ key3 };
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }
  in >> delS{ ":)" };

  if (in)
  {
    dest = DataStruct{ key1, key2, key3 };
  }
  return in;
}

std::ostream & kozlova::operator<<(std::ostream & out, const DataStruct & dest)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  ScopeGuard scopeGuard(out);
  out << "(:key1 " << std::fixed << std::setprecision(1) << dest.key1 << "d";
  out << ":key2 (:N " << dest.key2.first << ":D " << dest.key2.second << ":)";
  out << ":key3 ";
  out << std::quoted(dest.key3);
  out << ":)";
  return out;
}
