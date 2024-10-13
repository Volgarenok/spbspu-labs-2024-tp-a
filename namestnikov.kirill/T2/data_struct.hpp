#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>
#include <iostream>

namespace namestnikov
{
  struct DataStruct
  {
    bool operator<(const DataStruct & data) const;
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}
#endif
