#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <complex>
#include <string>

namespace kuznetsov
{
  struct DataStruct
  {
    DataStruct() :
      key1(1),
      key2(1.0, -1.0),
      key3("hi")
    {}

    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
  };

  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}

#endif
