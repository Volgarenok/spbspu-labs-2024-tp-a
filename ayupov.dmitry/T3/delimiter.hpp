#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace ayupov
{
  struct DelimiterChar
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterChar&& exp);
}
#endif