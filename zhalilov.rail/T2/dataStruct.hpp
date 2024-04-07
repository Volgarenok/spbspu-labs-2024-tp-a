#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>

namespace zhalilov
{
  struct DataStruct
  {
    double key1;
    long long key2;
    std::string key3;

    bool operator<(const DataStruct &other) const;
    bool operator>(const DataStruct &other) const;
    bool operator==(const DataStruct &other) const;
    bool operator<=(const DataStruct &other) const;
    bool operator>=(const DataStruct &other) const;
  };

  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &in, const DataStruct &data);
}

#endif
