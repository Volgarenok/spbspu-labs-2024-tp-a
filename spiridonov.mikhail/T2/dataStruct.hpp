#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <iostream>
#include <string>

namespace spiridonov
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
    bool operator<(const DataStruct& data) const;
  };

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::istream& operator>>(std::istream& in, std::string& exp);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}

#endif