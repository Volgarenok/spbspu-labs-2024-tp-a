#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>
#include <string>

namespace novokhatskiy
{
  struct Delimiter
  {
    char expected;
    bool toLow = false;
  };

  std::istream& operator>>(std::istream& in, Delimiter&& ex);

  struct DelimiterString
  {
    const char* expected;
    bool toLow = false;
  };

  std::istream& operator>>(std::istream& in, DelimiterString&& ex);

}

#endif
