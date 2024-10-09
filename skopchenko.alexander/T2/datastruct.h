#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <complex>
#include <string>
#include <utility>
#include <iostream>

namespace skopchenko
{

  struct DataStruct
  {
    std::complex<double> key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream &is, DataStruct &data);
  std::ostream &operator<<(std::ostream &os, const DataStruct &data);
  bool compare(const DataStruct &a, const DataStruct &b);

}

#endif
