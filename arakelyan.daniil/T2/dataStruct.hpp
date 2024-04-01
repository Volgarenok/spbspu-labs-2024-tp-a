#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <iostream>

namespace arakelyan
{
  struct DataStruct
  {
    DataStruct() = default;
    DataStruct(int f, int s):
      key1(f),
      key2(s)
    {}
    int key1;
    int key2;
  };
  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &out, DataStruct &data);
}

#endif
