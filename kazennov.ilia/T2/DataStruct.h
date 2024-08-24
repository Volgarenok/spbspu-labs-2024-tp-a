#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <string>
#include <iostream>

#include "Delimiter.h"

namespace kazennov
{
  struct DataStruct
  {
    bool operator<(const DataStruct& other) const;
    char key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}
#endif
