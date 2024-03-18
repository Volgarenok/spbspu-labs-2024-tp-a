#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP
#include <istream>

namespace zakozhurnikova
{
  struct Delimiter
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, const Delimiter&& exp);
}

#endif
