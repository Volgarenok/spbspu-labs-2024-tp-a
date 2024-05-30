#ifndef LIMITER_HPP
#define LIMITER_HPP

#include <iostream>

namespace chistyakov
{
  struct Limiter
  {
    const char * expected;
  };

  std::istream & operator>>(std::istream & in, Limiter && exp);
}

#endif
