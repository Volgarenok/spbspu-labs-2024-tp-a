#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <iostream>

namespace arakelyan
{
  struct DataStruct
  {
    // DataStruct() = default;
    // DataStruct(unsigned long long f, char s, std::string t):
    //   key1(f),
    //   key2(s),
    //   key3(t)
    // {}
    unsigned long long key1;
    char key2;
    std::string key3;
  };
  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &out, DataStruct &data);
}

#endif
