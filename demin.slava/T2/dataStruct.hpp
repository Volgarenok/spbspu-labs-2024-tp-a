#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include <iostream>

namespace demin
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;

    bool operator<(const DataStruct &src) const;
  };

  void parse(std::istream &in, double &src);
  void parse(std::istream &in, unsigned long long &src);
  void parse(std::istream &in, std::string &src);

  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &out, const DataStruct &data);
}

#endif
