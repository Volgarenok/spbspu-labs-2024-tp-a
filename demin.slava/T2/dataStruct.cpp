#include "dataStruct.hpp"
#include <iomanip>
#include <delimiter.hpp>
#include <streamGuard.hpp>
#include "formats.hpp"

bool demin::operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 == rhs.key1)
  {
    if (lhs.key2 == rhs.key2)
    {
      return lhs.key3.length() < rhs.key3.length();
    }
    return lhs.key2 < rhs.key2;
  }
  return lhs.key1 < rhs.key1;
}

std::istream &demin::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  in >> del{"("};
  const size_t KEYS_COUNT = 3;
  for (size_t i = 0; i < KEYS_COUNT; ++i)
  {
    size_t key = 0;
    in >> del{":key"} >> key;
    if (key == 1)
    {
      in >> DblLit{data.key1};
    }
    else if (key == 2)
    {
      in >> UllOct{data.key2};
    }
    else if (key == 3)
    {
      in >> StringVal{data.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> del{":)"};
  return in;
}

std::ostream &demin::operator<<(std::ostream &out, const DataStruct &data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard streamGuard(out);
  out << "(:key1 " << std::setprecision(1) << std::fixed << data.key1 << "d";
  out << ":key2 0" << std::oct << data.key2;
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}

