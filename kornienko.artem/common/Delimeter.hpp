#ifndef DELIMETER__H
#define DELIMETER_H
#include <iostream>

namespace kornienko
{
  struct Delimeter
  {
    char expected;
  };

  struct DelimeterString
  {
    std::string expected;
  };

  std::istream & operator>>(std::istream & in, const Delimeter && exp);
  std::istream & operator>>(std::istream & in, const DelimeterString && exp);
}

#endif
