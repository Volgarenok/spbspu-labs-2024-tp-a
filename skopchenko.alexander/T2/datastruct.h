#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <complex>
#include <string>
#include <utility>

namespace skopchenko
{

  struct DataStruct
  {
    std::complex<double> key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

}

#endif