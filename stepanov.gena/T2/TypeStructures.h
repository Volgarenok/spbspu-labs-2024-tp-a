#ifndef TYPESTRUCTURES_H
#define TYPESTRUCTURES_H

#include <iostream>

namespace stepanov
{

  struct BinUnsignedLongLongIO
  {
    explicit BinUnsignedLongLongIO(unsigned long long& ref);
    unsigned long long& ref_;
  };

  struct OctUnsignedLongLongIO
  {
    explicit OctUnsignedLongLongIO(unsigned long long& ref);
    unsigned long long& ref_;
  };

  struct StringIO
  {
    explicit StringIO(std::string& ref);
    std::string& ref_;
  };

  std::istream& operator>>(std::istream& in, BinUnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, OctUnsignedLongLongIO&& dest);
}

#endif
