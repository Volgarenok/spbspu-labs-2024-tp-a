#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>
#include <string>

namespace ayupov
{
  struct DelimiterChar
  {
    char expected;
  };
  struct DelimiterString
  {
    std::string text;
  };
  std::istream& operator>>(std::istream& in, DelimiterChar&& exp);
  std::istream& operator>>(std::istream& in, DelimiterString&& str);
}
#endif
