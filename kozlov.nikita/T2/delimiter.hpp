#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace kozlov
{
  struct DelimiterChr
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterChr&& exp);

  struct DelimiterStr
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterStr&& exp);
}
#endif
