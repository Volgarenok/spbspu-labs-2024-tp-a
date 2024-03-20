#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP
#include <istream>

namespace zakozhurnikova
{
  struct DelimiterChar
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, const DelimiterChar&& exp);
}

#endif
