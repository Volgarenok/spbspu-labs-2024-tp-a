#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <istream>

namespace marishin
{
  struct Delimeterchar
  {
    char expected;
  };

  struct Delimeterstring
  {
    const char* expected;
  };

  struct Delimeterpair
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimeterchar&& exp);
  std::istream& operator>>(std::istream& in, Delimeterstring&& exp);
  std::istream& operator>>(std::istream& in, Delimeterpair&& exp);
}

#endif
