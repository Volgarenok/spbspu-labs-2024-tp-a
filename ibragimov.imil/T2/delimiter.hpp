#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace ibragimov
{
  struct DelimiterI
  {
    char expected;
  };
  std::istream& operator>>(std::istream&, DelimiterI&&);

  struct StringI
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream&, StringI&&);
}

#endif
