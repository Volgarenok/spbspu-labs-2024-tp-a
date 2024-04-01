#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>

namespace chernikova
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    char* key3;
  };
  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
  bool compare(const DataStruct& value1, const DataStruct& value2);
}

#endif
