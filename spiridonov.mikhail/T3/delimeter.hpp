#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <istream>

namespace spiridonov
{
  struct DelimeterChar
  {
    char expected;
  };

  struct DelimeterString
  {
    const char* expected;
  };

  std::istream& operator>>(std::istream& in, DelimeterChar&& exp);
  std::istream& operator>>(std::istream& in, DelimeterString&& exp);
}

#endif
