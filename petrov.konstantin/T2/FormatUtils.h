#ifndef FORMAT_UTILS_H
#define FORMAT_UTILS_H

#include <string>
#include <iostream>

namespace petrov
{
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
  struct DelimiterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, SignedLongLongLiteralI&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongBinaryI&& dest);
  std::istream& operator>>(std::istream& in, StringI&& dest);
  std::istream& operator>>(std::istream& in, DelimiterI&& dest);
  std::string toBinary(unsigned long long src);
}
#endif
