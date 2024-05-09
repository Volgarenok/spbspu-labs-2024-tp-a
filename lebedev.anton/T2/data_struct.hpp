#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

namespace lebedev
{
  struct DataStruct
  {
    bool operator<(const DataStruct & other) const;

    double key1;
    double key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream & input, DataStruct & data);
  std::ostream & operator<<(std::ostream & output, const DataStruct & data);
}

#endif
