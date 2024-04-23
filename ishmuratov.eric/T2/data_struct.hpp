#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <complex>

namespace ishmuratov
{
  struct DataStruct
  {
    size_t key1;
    std::complex< double > key2;
    std::string key3;
    bool operator<(const DataStruct & other) const;
  };
  std::istream & operator>>(std::istream & input, DataStruct & value);
  std::ostream & operator<<(std::ostream & output, const DataStruct & value);
}

#endif
