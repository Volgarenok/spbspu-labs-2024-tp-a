#include "dataStruct.hpp"

std::ostream& ravinskij::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << data.key1 << ' ' << data.key2 << ' ' << data.key3;
  return out;
}
