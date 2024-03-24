#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include <cstring>
#include <iostream>
#include "delimiter.hpp"
namespace strelyaev
{
  struct DataStruct
  {
    signed long long key1_;
    signed long long key2_;
    std::string key3_;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    using del = delimiter;
    in >> del{'('} >> del{':'};
    in >> del{'k'} >> del{'e'} >> del{'y'};
    int key_num = 0;
    in >> key_num;
    if (key_num == 1)
    {
      std::cout << "1\n";
    }
    if (key_num == 2)
    {
      std::cout << "2\n";
    }
  }
}
#endif
