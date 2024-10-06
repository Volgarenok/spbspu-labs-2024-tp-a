#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <complex>
#include <utility>

namespace zhakha
{
  struct DataStruct
  {
    double key1 = 0.0;
    long long key2 = 0;
    std::string key3 = "";
  };
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}

std::ostream& operator<<(std::ostream& out, const std::pair<long long, unsigned long long>& pair);
std::istream& operator>>(std::istream& in, std::pair<long long, unsigned long long>& pair);


#endif
