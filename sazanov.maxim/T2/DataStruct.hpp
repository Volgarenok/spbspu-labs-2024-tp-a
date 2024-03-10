#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <utility>

namespace sazanov
{
  struct DataStruct
  {
    DataStruct(unsigned long long otherKey1, char otherKey2, std::string  otherKey3):
      key1(otherKey1),
      key2(otherKey2),
      key3(std::move(otherKey3))
    {}

    unsigned long long key1;
    char key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream& in, DataStruct& value);
}

#endif //DATA_STRUCT_HPP
