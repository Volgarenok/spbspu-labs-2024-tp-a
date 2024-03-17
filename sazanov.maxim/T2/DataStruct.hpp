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
  void parseBinaryNumber(std::istream& in, unsigned long long& key);
  void parseCharLiteral(std::istream& in, char& key);
  void parseStringKey(std::istream& in, std::string& key);
}

#endif
