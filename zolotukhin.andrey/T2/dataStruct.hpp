#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <cstring>
namespace zolotukhin
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };
}
#endif
