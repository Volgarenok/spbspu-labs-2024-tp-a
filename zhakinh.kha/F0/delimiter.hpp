#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace zhakha
{
  struct DelimiterString
  {
    const char* expected;
  };
  struct DelimiterChar
  {
    char expected;
  };
  struct DelimiterIsAlpha
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterChar&& exp);
  std::istream& operator>>(std::istream& in, DelimiterString&& exp);
  std::istream& operator>>(std::istream& in, DelimiterIsAlpha&& exp);

}
#endif
