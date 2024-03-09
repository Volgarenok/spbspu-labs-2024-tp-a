#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>

namespace novikov
{
  struct DataStruct
  {
    using ull = unsigned long long;
    ull key1;
    ull key2;
    std::string key3;
  };
}

#endif