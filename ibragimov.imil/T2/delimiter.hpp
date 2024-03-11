#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>
#include <string>

namespace ibragimov
{
  struct Delimiter
  {
    const char* expected;
  };
  std::istream& operator>>(std::istream&, Delimiter&&);
}

#endif
