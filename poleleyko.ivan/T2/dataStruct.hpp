#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include <iosfwd>
namespace poleleyko
{
  struct DataStruct
  {
    signed long long key1;
    unsigned long long key2;
    std::string key3;
  };
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}
#endif