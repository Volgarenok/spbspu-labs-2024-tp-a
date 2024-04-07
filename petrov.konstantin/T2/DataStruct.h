#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>

namespace petrov
{
  struct DataStruct
  {
    long long key1;
    unsigned long long key2;
    std::string key3;
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
  bool operator<(const DataStruct& left, const DataStruct& right);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::istream& operator>>(std::istream& in, SignedLongLongLiteralI&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongBinaryI&& dest);
  std::istream& operator>>(std::istream& in, StringI&& dest);
  std::istream& operator>>(std::istream& in, DelimiterI&& dest);
  std::istream& operator>>(std::istream& in, LabelI&& dest);
}
#endif
