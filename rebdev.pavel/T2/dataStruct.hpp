#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>

#include "hexType.hpp"
#include "binType.hpp"
#include "stringType.hpp"

namespace rebdev
{
  struct DataStruct
  {
    binType key1_;
    hexType key2_;
    stringType key3_;

    bool operator<(const DataStruct & rhs) const;
  };

  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}

#endif
