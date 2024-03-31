#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <istream>

namespace rebdev
{
  struct delimeter_t
  {
    char expected;
  };

  std::istream & operator>>(std::istream & in, delimeter_t && exp);
}

#endif
