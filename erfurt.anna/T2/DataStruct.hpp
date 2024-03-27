#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>

namespace erfurt
{
  struct DataStruct
  {
    long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3 = "";

    bool operator<(const DataStruct& value) const;
  };

  std::istream &operator>>(std::istream &in, DataStruct &value);
  std::ostream &operator<<(std::ostream &out, const DataStruct &value);
}

#endif //DATA_STRUCH_HPP

