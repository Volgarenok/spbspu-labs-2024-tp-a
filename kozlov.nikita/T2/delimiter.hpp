#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace kozlov
{
  struct DelimiterCh
  {
    char expected;
  };

  struct DelimiterStr
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterCh&& exp);
  std::istream& operator>>(std::istream& in, DelimiterStr&& exp);
}
#endif
