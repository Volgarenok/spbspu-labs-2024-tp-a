#ifndef DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_HPP

#include <complex>
#include <iostream>
#include <string>

namespace ibragimov
{
  struct DataStructure
  {
    double key1;
    std::complex< double > key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream&, DataStructure&);
  std::ostream& operator<<(std::ostream&, const DataStructure&);
  bool operator<(const DataStructure&, const DataStructure&);
}

#endif
