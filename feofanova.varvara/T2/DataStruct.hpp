#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>

namespace feofanova
{
  struct LitI
  {
    double& value;
  };
  std::istream& operator>>(std::istream& in, LitI&& num);

  struct BinI
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, BinI&& num);

  struct BinO
  {
    unsigned long long value;
  };
  std::ostream& operator<<(std::ostream& out, BinO&& src);

  struct StringI
  {
    std::string& str;
  };
  std::istream& operator>>(std::istream& in, StringI&& num);

  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
    bool operator<(const DataStruct& other) const;
  };

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}
#endif
