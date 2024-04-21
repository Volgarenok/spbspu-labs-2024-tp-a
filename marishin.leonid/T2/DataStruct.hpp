#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>

namespace marishin
{
  struct DataStruct
  {
    double key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
    bool operator<(const DataStruct& data) const;
    bool operator>(const DataStruct& data) const;
    bool operator<=(const DataStruct& data) const;
    bool operator>=(const DataStruct& data) const;
    bool operator==(const DataStruct& data) const;
    bool operator!=(const DataStruct& data) const;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}

#endif
