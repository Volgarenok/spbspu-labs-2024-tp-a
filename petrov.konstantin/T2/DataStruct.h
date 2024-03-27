#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
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
  struct TypeI
  {
    DataStruct& dataStruct;
  };
  struct SignedLongLongLiteralI
  {
    long long& ref;
  };
  struct UnsignedLongLongBinaryI
  {
    unsigned long long& ref;
  };
  struct StringI
  {
    std::string& ref;
  };
  struct DelimiterI
  {
    char expected;
  };
  struct LabelI
  {
    std::string expected;
  };
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::istream& operator>>(std::istream& in, TypeI&& dest);
  std::istream& operator>>(std::istream& in, SignedLongLongLiteralI&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongBinaryI&& dest);
  std::istream& operator>>(std::istream& in, StringI&& dest);
  std::istream& operator>>(std::istream& in, DelimiterI&& dest);
  std::istream& operator>>(std::istream& in, LabelI&& dest);
}
#endif
