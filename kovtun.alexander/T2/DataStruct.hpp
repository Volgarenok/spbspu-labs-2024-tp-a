#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

#include "IOScopeGuard.hpp"
#include "Delimiter.hpp"

namespace kovtun
{
  struct DataStruct
  {
    double key1;
    char key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}

#endif
