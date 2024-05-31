#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>
#include <iosfwd>

namespace ponamarev
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
    bool operator<(const DataStruct& other) const;
  };
  std::istream& operator>>(std::istream& in, DataStruct& obj);
  std::ostream& operator<<(std::ostream& out, const DataStruct& obj);
}

#endif
