#ifndef DATA_STRUCT
#define DATA_STRUCT

#include <iostream>
#include <string>

namespace stepanchenko
{
  struct DataStruct
  {
    long long key1_;
    char key2_;
    std::string key3_;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  bool operator<(const DataStruct& data1, const DataStruct& data2);
}

#endif
