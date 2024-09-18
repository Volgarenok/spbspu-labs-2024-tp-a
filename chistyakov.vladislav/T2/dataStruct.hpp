#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <cstring>
#include "dataTypes.hpp"

namespace chistyakov
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;

    bool operator<(const DataStruct & data) const;
  };

  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}

#endif
