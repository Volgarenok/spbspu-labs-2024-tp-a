#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iosfwd>

namespace erohin
{
  struct DataStruct
  {
    double key1;
    long long ke2;
    std::string key3;
  };

  std::istream & operator>>(std::istream & input, DataStruct & dest);
}

#endif
