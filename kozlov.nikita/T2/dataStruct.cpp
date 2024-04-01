#include "dataStruct.hpp"
#include "delimiter.hpp"

std::istream& operator>>(std::istream& in, DataStruct&& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard streamGuard(in);
  using del = Delimiter;
  int keyCount = 0;
  DataStruct temp{0, '', ""};
}
