#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <complex>
#include <string>

namespace sivkov
{
  struct DataStruct
  {
    bool operator<(const DataStruct& value) const;
    double key1;
    std::complex< double > key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}

#endif
