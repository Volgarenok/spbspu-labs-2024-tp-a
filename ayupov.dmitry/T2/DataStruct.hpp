#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <istream>
#include <ostream>

namespace ayupov
{
  struct DataStruct
  {
    double key1;
    char key2;
    std::string key3;
    bool operator<(const DataStruct& other) const;
  };
  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}
#endif
