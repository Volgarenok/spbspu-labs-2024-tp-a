#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
#include <iostream>

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
  struct LongLongI
  {
    long long& ref;
  };
  struct DelimeterI
  {
    char expected;
  };
  struct LabelI
  {
    std::string expected;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::istream& operator>>(std::istream& in, LongLongI&& dest);
  std::istream& operator>>(std::istream& in, DelimeterI&& dest);
  std::istream& operator>>(std::istream& in, LabelI&& dest);

}

#endif
