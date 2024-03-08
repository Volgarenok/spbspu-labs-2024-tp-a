#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include <utility>
#include <istream>
#include <ostream>

namespace piyavkin
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3; 
  };
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data); 
}
#endif