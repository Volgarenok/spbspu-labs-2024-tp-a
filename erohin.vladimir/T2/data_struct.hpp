#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iosfwd>

namespace erohin
{
  struct DataStruct
  {
    double key1;
    long long key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream & input, DataStruct & dest);
  std::ostream & operator<<(std::ostream & output, const DataStruct & dest);
  bool operator<(const DataStruct & lhs, const DataStruct & rhs);
}

#endif
