#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
namespace lopatina
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

  bool operator<(const DataStruct & first, const DataStruct & second);
  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}

#endif
