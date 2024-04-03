#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace chistyakov
{
  struct Delimiter
  {
    const char * expected;
  };

  std::istream & operator>>(std::istream & in, Delimiter && exp);
}

#endif
