#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <iostream>

namespace spiridonov
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  bool operator<(const DataStruct& firstData, const DataStruct& secondData);
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}

#endif
