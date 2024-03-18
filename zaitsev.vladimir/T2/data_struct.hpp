#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>
#include <iostream>

namespace zaitsev
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
    
    bool operator<(const DataStruct& other) const;
  };

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::istream& out, const DataStruct& data);
}
#endif 

