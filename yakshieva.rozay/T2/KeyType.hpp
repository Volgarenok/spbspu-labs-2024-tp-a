#ifndef KEY_TYPE_HPP
#define KEY_TYPE_HPP

#include <string>

namespace yakshieva
{
  struct DoubleIO
  {
    double& ref;
  };
  struct BinaryIO
  {
    unsigned long long& value;
  };
  struct StringIO
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, BinaryIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
