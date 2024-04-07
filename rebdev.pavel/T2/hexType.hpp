#ifndef HEXTYPE_HPP
#define HEXTYPE_HPP

#include <iostream>

namespace rebdev
{
  struct hexType
  {
    unsigned long long data_;

    bool operator==(const hexType & hex) const noexcept;
    bool operator<(const hexType & hex) const noexcept;
  };

  std::istream & operator>>(std::istream & in, hexType & hex);
  std::ostream & operator<<(std::ostream & out, const hexType & hex);
}

#endif
