#ifndef FORMAT_UTILS_H
#define FORMAT_UTILS_H

#include <string>
#include <iostream>

namespace petrov
{
  struct UnsignedLongLongBinaryO
  {
    unsigned long long val;
  };
  struct SignedLongLongLiteralI
  {
    long long& ref;
  };
  struct UnsignedLongLongBinaryI
  {
    unsigned long long& ref;
  };
  struct StringI
  {
    std::string& ref;
  };
  std::ostream& operator<<(std::ostream& out, const UnsignedLongLongBinaryO&& src);
  std::istream& operator>>(std::istream& in, SignedLongLongLiteralI&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongBinaryI&& dest);
  std::istream& operator>>(std::istream& in, StringI&& dest);
}
#endif
