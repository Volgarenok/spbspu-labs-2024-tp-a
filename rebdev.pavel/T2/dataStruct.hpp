#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

namespace rebdev
{
  struct DataStruct
  {
    unsigned long long key1_;
    unsigned long long key2_;
    std::string key3_;

    bool operator<(const DataStruct & rhs) const;
  };

  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}

#endif
