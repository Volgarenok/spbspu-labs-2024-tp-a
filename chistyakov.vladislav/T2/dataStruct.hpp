#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <cstring>
#include "dataTypes.hpp"

namespace chistyakov
{
  struct DataStruct
  {
    UllBin key1;
    RatLsp key2;
    StringT key3;

    bool operator>(const DataStruct & data) const;
  };

  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}

#endif
