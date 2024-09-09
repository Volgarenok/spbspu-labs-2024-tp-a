#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>

namespace vojuck
{
  struct DataStruct
  {
    unsigned long long  key1;
    char key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream& in, DataStruct& dest); //destenation
  std::ostream &operator<<(std::ostream& out,const DataStruct& dest);
  bool operator <(const DataStruct &leftkey, const DataStruct &rightkey);
}

#endif
