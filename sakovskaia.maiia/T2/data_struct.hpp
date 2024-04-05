#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <cstring>
namespace sakovskaia
{
  struct DataStruct
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream & input, DataStruct & data_struct);
  bool operator<(DataStruct & begin, DataStruct & end);
}
#endif
