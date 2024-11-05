#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>

namespace petuhov {
  struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream& in, DataStruct& data);
  std::ostream &operator<<(std::ostream& out, const DataStruct& data);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
