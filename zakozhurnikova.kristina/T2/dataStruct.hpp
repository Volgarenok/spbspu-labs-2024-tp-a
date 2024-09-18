#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>
#include <istream>
#include <ostream>

namespace zakozhurnikova
{
  struct DataStruct
  {
    using ull = unsigned long long;
    double key1;
    ull key2;
    std::string key3;

    bool operator<(const DataStruct& rhs) const;
  };

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}
#endif
