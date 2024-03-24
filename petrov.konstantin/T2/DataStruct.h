#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>

namespace petrov
{
  struct DataStruct
  {
    long long key1_;
    unsigned long long key2_;
    std::string key3_;

    DataStruct() = default;
    DataStruct(long long key1, unsigned long long key2, const std::string& key3);
    DataStruct(const DataStruct&) = default;
    DataStruct(DataStruct&&) = default;
    ~DataStruct() = default;
    DataStruct& operator=(const DataStruct&) = default;
    DataStruct& operator=(DataStruct&&) = default;
    bool operator<(const DataStruct& other) const;
  };
}

#endif
