#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace vyzhanov
{
  struct Delimeter
  {
    const char expected;
  };

  struct DelimeterLit
  {
    size_t& ref;
  };

  struct DelimeterOct
  {
    size_t& ref;
  };

  struct DelimeterString
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream&, Delimeter&&);
  std::istream& operator>>(std::istream&, DelimeterLit&&);
  std::istream& operator>>(std::istream&, DelimeterOct&&);
  std::istream& operator>>(std::istream&, DelimeterString&&);
}

#endif
