#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include <iostream>

namespace altun
{
  struct DoubleScience
  {
    const double& data_;
  };
  std::ostream& operator<<(std::ostream&, const DoubleScience&);

  struct DataStruct
  {
    double key1;
    double key2;
    std::string key3;
  };
  bool operator<(const DataStruct&, const DataStruct&);
  std::istream& operator>>(std::istream&, DataStruct&);
  std::ostream& operator<<(std::ostream&, const DataStruct&);
}
#endif
