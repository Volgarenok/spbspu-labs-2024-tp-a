#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iosfwd>

namespace sazanov
{
  struct DataStruct
  {
    unsigned long long key1;
    char key2;
    std::string key3;

    bool operator<(const DataStruct& other) const;
  };
  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& stream, const DataStruct& value);
}

#endif
