#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <cstddef>
#include <complex>
#include <iostream>

namespace grechishnikov
{
  struct DataStruct
  {
    size_t key1;
    std::complex< double > key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  bool operator<(const DataStruct& first, const DataStruct& second);

  std::ostream& operator<<(std::ostream& out, const std::complex< double >& comp);
}

#endif
