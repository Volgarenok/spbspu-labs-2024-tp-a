#ifndef DELIMETER__H
#define DELIMETER_H
#include <iostream>

namespace kornienko
{
  struct Delimeter
  {
    char expected;
  };

  std::istream & operator>>(std::istream & in, const Delimeter && exp);
}

#endif
