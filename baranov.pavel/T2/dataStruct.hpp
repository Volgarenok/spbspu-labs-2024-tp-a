#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>
#include <complex>

namespace baranov
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
    bool operator<(const DataStruct & rhs) const;
  };

  std::istream & operator>>(std::istream &, DataStruct & data);
  std::ostream & operator<<(std::ostream &, const DataStruct & data);
}

#endif

