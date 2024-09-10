#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <complex>
#include <iostream>
#include <string>

namespace allaberdiev
{
  struct DataStruct
  {
    std::complex< double > key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };
  bool operator<(const DataStruct& l, const DataStruct& r);
  std::istream& operator>>(std::istream&, DataStruct&);
  std::ostream& operator<<(std::ostream&, const DataStruct&);
}
#endif
