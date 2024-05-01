#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <istream>

namespace kuzmina
{
  struct DelimiterI
  {
    const char expected;
  };

  std::istream& operator>>(std::istream&, DelimiterI&&);
}

#endif
