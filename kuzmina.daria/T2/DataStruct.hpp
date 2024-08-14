#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <utility>
#include <string>
#include <iostream>

namespace kuzmina
{
  struct DataStruct
  {
    long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;

    bool operator<(const DataStruct&) const;
  };

  std::istream& operator>>(std::istream&, DataStruct&);
  std::ostream& operator<<(std::ostream&, const DataStruct&);
}

#endif
