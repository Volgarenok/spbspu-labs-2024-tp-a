#ifndef DELIMETERS_HPP
#define DELIMETERS_HPP
#include <istream>

namespace zakozhurnikova
{
  struct Delimeter
  {
    char expected;
  }
;
  std::istream& operator>>(std::istream& in, const DelimiterI& exp);
}
#endif
