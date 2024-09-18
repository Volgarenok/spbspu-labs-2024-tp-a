#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>
#include <iosfwd>
namespace sakovskaia
{
  struct DataStruct
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream & input, DataStruct & data_struct);
  bool operator<(const DataStruct & begin, const DataStruct & end);
  std::ostream & operator<<(std::ostream & output, const DataStruct & data_struct);
}
#endif
