#ifndef KEY_TYPE_HPP
#define KEY_TYPE_HPP

#include <iostream>
#include <string>

namespace yakshieva
{
  struct DoubleIn
  {
    double& ref;
  };
  struct DoubleOut
  {
    double ref;
  };
  struct BinaryIO
  {
    unsigned long long& value;
  };
  struct StringIO
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream& in, DoubleIn&& dest);
  std::ostream& operator<<(std::ostream& out, const DoubleOut&& exp);
  std::istream& operator>>(std::istream& in, BinaryIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
