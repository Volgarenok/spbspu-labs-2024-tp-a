#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>

namespace felk
{
  struct DataStruct
  {
    long long key1;
    size_t key2;
    std::string key3;
    bool operator<(const DataStruct& other) const;
   };
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}

#endif
