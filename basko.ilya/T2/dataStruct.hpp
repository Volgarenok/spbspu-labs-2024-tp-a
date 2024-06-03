#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>
#include <complex>

namespace basko
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
    bool operator<(const DataStruct& data) const;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}

#endif
