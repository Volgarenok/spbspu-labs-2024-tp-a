#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

#include "notDecimalNumber.hpp"

namespace rebdev
{
  struct dataStruct_t
  {
    rebdev::notDecimalNumber_t key1_{0, 0, 2};
    rebdev::notDecimalNumber_t key2_{0, 0, 16};
    std::string key3_;

    bool operator < (const dataStruct_t & rhv) const;
    bool operator > (const dataStruct_t & rhv) const;
  };

  std::istream & operator >> (std::istream & in, dataStruct_t & data);
  std::ostream & operator << (std::ostream & out, const dataStruct_t & data);
}

#endif
