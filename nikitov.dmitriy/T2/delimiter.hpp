#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <fstream>

namespace nikitov
{
  struct DelimiterString
  {
    const char* expected;
  };

  struct Delimiter
  {
    char expected;
  };

  std::istream& operator>>(std::istream& input, DelimiterString delimiter);
  std::istream& operator>>(std::istream& input, Delimiter delimiter);

}
#endif