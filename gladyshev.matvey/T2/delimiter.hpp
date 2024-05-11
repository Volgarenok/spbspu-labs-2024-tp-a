#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace gladyshev
{
  struct Delimiter
  {
    const char * exp;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& exp);
}

#endif
