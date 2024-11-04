#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace skopchenko
{
  struct delimiter_t
  {
    char expected;
    bool checkCase;
    explicit delimiter_t(char ex, bool check = true);
  };
  std::istream& operator>>(std::istream& in, delimiter_t&& exp);
}
#endif
