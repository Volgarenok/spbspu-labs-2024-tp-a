#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include <cstring>
#include <iostream>
#include "delimiter.hpp"
namespace strelyaev
{
  struct DataStruct
  {
    signed long long key1_;
    signed long long key2_;
    std::string key3_;
    bool operator<(const DataStruct& other) const;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}
#endif
