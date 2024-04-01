#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& kozlov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard streamGuard(in);
  using del = Delimiter;
  int keyCount = 0;
  DataStruct temp{0, 0, ""};
  data = temp;
  return in;
}
