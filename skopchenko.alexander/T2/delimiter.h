#ifndef DELIMITER_H
#define DELIMITER_H

#include <iostream>
#include <string>

namespace skopchenko
{

  struct Delimiter
  {
    const char *exp;
  };

  std::istream &operator>>(std::istream &in, Delimiter &&exp);

}

#endif
