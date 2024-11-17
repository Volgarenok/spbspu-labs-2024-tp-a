#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <iostream>
#include <string>

namespace chernov
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& input, DataStruct& obj);
  std::ostream& operator<<(std::ostream& output, const DataStruct& obj);

  bool operator<(const DataStruct& value1, const DataStruct& value2);
}

#endif
