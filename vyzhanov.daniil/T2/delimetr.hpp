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

  std::istream& operator>>(std::istream& in, Delimeter&& val);
  std::istream& operator>>(std::istream& in, DelimeterLit&& val);
  std::istream& operator>>(std::istream& in, DelimeterOct&& val);
  std::istream& operator>>(std::istream& in, DelimeterString&& val);
}

#endif
