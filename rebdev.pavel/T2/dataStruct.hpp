#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

namespace rebdev
{
  struct dataStruct
  {
    unsigned long long key1_;
    unsigned long long key2_;
    std::string key3_;
  };

  std::istream & operator >> (std::istream & in, dataStruct & data);
  std::ostream & operator << (std::ostream & out, const dataStruct & data);
}

#endif
