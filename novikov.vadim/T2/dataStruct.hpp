#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <istream>
#include <ostream>

namespace novikov
{
  struct DataStruct
  {
    using ull = unsigned long long;
    ull key1;
    ull key2;
    std::string key3;
  };
  bool operator<(const DataStruct& value1, const DataStruct& value2);
  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}

#endif
