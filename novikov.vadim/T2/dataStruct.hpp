#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

namespace novikov
{
  struct DataStruct
  {
    using ull = unsigned long long;
    ull key1;
    ull key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, DataStruct& value);
}

#endif