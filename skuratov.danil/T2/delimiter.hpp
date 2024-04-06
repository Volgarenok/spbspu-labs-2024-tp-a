#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace skuratov
{
  struct DelimiterI
  {
    const char expected;
  };
  std::istream& operator>>(std::istream& in, const DelimiterI&& exp);
}

#endif
