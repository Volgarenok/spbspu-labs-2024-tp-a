#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include<string>

namespace kozakova {
  struct DataStruct
  {
    bool operator<(const DataStruct& value) const;
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}
#endif
