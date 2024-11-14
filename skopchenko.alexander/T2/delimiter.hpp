#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace skopchenko
{
  struct delimiter_t
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, delimiter_t&& exp);

  struct SensitiveDel
  {
    char expected;
    bool checkCase;
    SensitiveDel(char ex, bool check);
  };
  std::istream& operator>>(std::istream& in, SensitiveDel&& exp);
}
#endif
