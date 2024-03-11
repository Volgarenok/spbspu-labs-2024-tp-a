#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iosfwd>

namespace zhalilov
{
  struct DataStruct
  {
    DataStruct();
    DataStruct(double key1, long long key2, const std::string &key3);

  private:
    double key1_;
    long long key2_;
    std::string key3_;
  };

  std::istream &operator>>(std::istream &in, DataStruct &data);
}

#endif
