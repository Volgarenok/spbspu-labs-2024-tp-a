#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>

namespace kartamyshev
{
  struct DataStruct
  {
    double key1;
    long long key2;
    std::string key3;
    bool operator<(const DataStruct& value) const;
  };

  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}
#endif
