#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iosfwd>

namespace demidenko
{
  struct DelimeterI
  {
    const char* delimeter_;
  };

  std::istream& operator>>(std::istream& in, DelimeterI&& del);
}

#endif
