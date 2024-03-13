#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <complex>
#include <string>

namespace kuznetsov
{
  struct DataStruct
  {
    DataStruct():
     key1(0),
     key2(0),
     key3("")
    {}
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
  };
}

#endif //DATA_STRUCT_H
