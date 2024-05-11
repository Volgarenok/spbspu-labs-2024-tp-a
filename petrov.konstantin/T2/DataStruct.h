#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>

namespace petrov
{
  struct DataStruct
  {
    long long key1;
    unsigned long long key2;
    std::string key3;
  };
  bool operator<(const DataStruct& left, const DataStruct& right);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
}
#endif
