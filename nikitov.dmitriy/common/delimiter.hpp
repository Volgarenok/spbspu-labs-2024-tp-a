#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace nikitov
{
  struct DelimiterString
  {
    const char* expected;
  };

  struct DelimiterChar
  {
    char expected;
  };

  std::istream& operator>>(std::istream& input, DelimiterString&& delimiter);
  std::istream& operator>>(std::istream& input, DelimiterChar&& delimiter);
}
#endif
