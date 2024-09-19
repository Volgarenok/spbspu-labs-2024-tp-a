#ifndef READ_IO_H
#define READ_IO_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

namespace serter
{
  struct DelimiterIO
  {
    char expected;
  };
  struct LongLongIO
  {
    long long& reference;
  };
  struct StringIO
  {
    std::string& reference;
  };
  struct WordIO
  {
    std::string& reference;
  };
  struct BinaryIO
  {
    unsigned long long& reference; // "refence" -> "reference"
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& delimeter);
  std::istream& operator>>(std::istream& in, LongLongIO&& number);
  std::istream& operator>>(std::istream& in, StringIO&& string);
  std::istream& operator>>(std::istream& in, WordIO&& string);
  std::istream& operator>>(std::istream& in, BinaryIO&& binaryNumber);
  std::string toBinary(unsigned long long decimalNumber);
  unsigned long long toDecimal(const std::string& binaryNumber);
}

#endif

