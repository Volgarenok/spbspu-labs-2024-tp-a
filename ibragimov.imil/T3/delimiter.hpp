#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>

namespace ibragimov
{
  namespace detail
  {
    struct Delimiter
    {
      const char expected;
    };
    std::istream& operator>>(std::istream&, Delimiter&&);
  }
}

#endif
