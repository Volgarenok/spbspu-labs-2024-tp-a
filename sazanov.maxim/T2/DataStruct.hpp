#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <utility>

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
  void parseKey(std::istream& in, unsigned long long& key);
  void parseKey(std::istream& in, char& key);
  void parseKey(std::istream& in, std::string& key);
  std::string getBinary(unsigned long long n);
}

#endif
