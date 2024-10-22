#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <complex>
#include <iostream>
#include <string>

namespace vorobieva {
struct DataStruct {
  std::complex<double> key1;
  unsigned long long key2;
  std::string key3;

  bool operator<(const DataStruct &data) const;
};

std::istream &operator>>(std::istream &in, DataStruct &value);
std::ostream &operator<<(std::ostream &out, const DataStruct &value);
}

#endif
