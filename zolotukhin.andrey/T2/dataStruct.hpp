#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include <utility>
#include <iostream>
namespace zolotukhin
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}
#endif
