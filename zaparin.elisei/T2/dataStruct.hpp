#ifndef DATA_STRUCT
#define DATA_STRUCT

#include<string>
#include<istream>
#include<ostream>

namespace zaparin
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;

    bool operator<(const DataStruct& data);
  };

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}

#endif

