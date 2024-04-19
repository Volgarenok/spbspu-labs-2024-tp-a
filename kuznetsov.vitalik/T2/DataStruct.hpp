#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <complex>
#include <string>

namespace kuznetsov
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;

    bool operator<(const DataStruct& data) const;
  };

  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  std::istream& operator>>(std::istream& in, DataStruct& data);
}

#endif

