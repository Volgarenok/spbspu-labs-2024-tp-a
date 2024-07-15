#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <utility>

namespace zhakha
{
  struct DataStruct
  {
    double key1 = 0.0;
    std::pair< long long, unsigned long long > key2 = {0, 0};
    std::string key3 = "";
  };
  
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}
#endif
