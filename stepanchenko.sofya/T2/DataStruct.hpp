#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

#include "Delimiters.hpp"
#include "Formats.hpp"

namespace stepanchenko
{
  struct DataStruct
  {
    long long key1_;
    char key2_;
    std::string key3_;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  bool operator<(const DataStruct& data1, const DataStruct& data2);
}

#endif
