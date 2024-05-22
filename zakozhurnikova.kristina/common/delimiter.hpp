#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP
#include <istream>

namespace zakozhurnikova
{
  struct Delimiter
  {
    const char* delimiter;
  };

  std::istream& operator>>(std::istream& in, const Delimiter&& exp);
}
#endif
