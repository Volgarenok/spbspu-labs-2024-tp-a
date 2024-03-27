#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP
#include <istream>

namespace zakozhurnikova
{
  struct DelimiterChar
  {
    char delimiter;
  };

  std::istream& operator>>(std::istream& in, const DelimiterChar&& exp);

  struct DelimiterString
  {
    const char* delimiter;
  };

  std::istream& operator>>(std::istream& in, DelimiterString&& exp);
}

#endif
