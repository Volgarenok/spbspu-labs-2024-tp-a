#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>

namespace belokurskaya
{
  struct DataStruct
  {
    char key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;

    bool operator<(const DataStruct& other) const;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

#endif
