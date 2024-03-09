#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <istream>

namespace novikov
{
  struct DelimiterI
  {
    char expected;
  };
  std::istream operator>>(std::istream& in, const DelimiterI& exp);
}

#endif