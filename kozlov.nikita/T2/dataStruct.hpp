#ifndef DATA_STRUCT_HPP
#define DARA_STRUCT_HPP
#include <iostream>
#include <string>

namespace kozlov
{
  struct DataStruct
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream out, const DataStruct& data);
}
#endif
