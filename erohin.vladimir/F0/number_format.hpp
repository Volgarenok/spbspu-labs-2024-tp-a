#ifndef NUMBER_FORMAT_HPP
#define NUMBER_FORMAT_HPP

#include <iosfwd>

namespace erohin
{
  enum numformat_t
  {
    NUMBER,
    PROPORTION,
    FRACTIONAL,
    PERCENTAGE
  };

  struct NumberFormat
  {
    size_t number;
    size_t size;
    numformat_t format;
  };

  std::ostream & operator<<(std::ostream & output, NumberFormat && numformat);
}

#endif
