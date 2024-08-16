#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <Delimiter.hpp>

namespace artemev
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;

    bool operator<(const DataStruct& oth) const;
  };

std::istream& operator>>(std::istream& in, DataStruct& value);
std::ostream& operator<<(std::ostream& out, const DataStruct& value);

}

#endif
