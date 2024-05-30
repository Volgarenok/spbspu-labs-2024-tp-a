#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iosfwd>
#include <string>
#include <complex>

namespace isaychev
{
  struct DataStruct
  {
    long long key1;
    std::complex< double > key2;
    std::string key3;
    bool operator<(const DataStruct & other) const;
  };

  std::istream & operator>>(std::istream & in, DataStruct & obj);
  std::ostream & operator<<(std::ostream & out, const DataStruct & obj);
}

#endif
