#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <complex>

namespace isaychev
{
  struct DataStruct
  {
    long long key1;
    std::complex< double > key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream & in, DataStruct & obj);
  std::ostream & operator<<(std::ostream & out, const DataStruct & obj);
}

#endif
