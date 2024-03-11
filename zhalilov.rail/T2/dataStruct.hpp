#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>

namespace zhalilov
{
  struct DataStruct
  {
    DataStruct();

    DataStruct(double key1, long long key2, std::string key3):
      key1_(key1),
      key2_(key2),
      key3_(key3)
    {}

  private:
    double key1_;
    long long key2_;
    std::string key3_;
  };
}

#endif
