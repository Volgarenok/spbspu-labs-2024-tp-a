#ifndef BINTYPE_HPP
#define BINTYPE_HPP

#include <iostream>

namespace rebdev
{
  struct binType
  {
    unsigned long long data_;

    bool operator==(const binType & bin) const noexcept;
    bool operator<(const binType & bin) const noexcept;
  };

  std::istream & operator>>(std::istream & in, binType & bin);
  std::ostream & operator<<(std::ostream & out, const binType & bin);
}

#endif

