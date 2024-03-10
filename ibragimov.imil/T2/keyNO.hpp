#ifndef KEY_NO_HPP
#define KEY_NO_HPP

#include <istream>

namespace ibragimov
{
  struct KeyNO
  {
    unsigned NO = 0;
  };
  std::istream& operator>>(std::istream&, KeyNO&);
}

#endif
