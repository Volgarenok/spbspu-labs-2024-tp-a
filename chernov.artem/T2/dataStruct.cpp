#include "dataStruct.hpp"
#include "streamGuard.hpp"

namespace chernov
{
  std::istream& operator>>(std::istream& input, DataStruct& obj)
  {}

  std::ostream& operator<<(std::ostream& output, const DataStruct& obj)
  {}

  bool operator<(const DataStruct& value1, const DataStruct& value2)
  {
    return (value1.key1 < value2.key1) || (value1.key2 < value2.key2) || (value1.key3.size() < value2.key3.size());
  }
}
