#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

namespace chernikova
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
  bool operator<(const DataStruct& value1, const DataStruct& value2);
}

#endif
