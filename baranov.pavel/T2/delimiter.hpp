#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace baranov
{
  struct DelimiterI
  {
    char exp;
  };

  std::istream & operator>>(std::istream & in, Delimiter && dest);
}

#endif

