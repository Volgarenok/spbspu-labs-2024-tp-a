#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <iostream>

namespace stepanov
{
  struct DataStruct
  {
    unsigned long long key1_;
    unsigned long long key2_;
    std::string key3_;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
  bool operator<(const DataStruct& first, const DataStruct& second);
}

#endif
