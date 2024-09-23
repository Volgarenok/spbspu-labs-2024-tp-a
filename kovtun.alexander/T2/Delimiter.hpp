#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

namespace kovtun
{
  struct DelimiterI
  {
    char expected;
  };

  struct KeyI
  {
    int & number;
  };

  struct DoubleLitI
  {
    double & dl;
  };

  std::istream & operator>>(std::istream & in, DelimiterI && delimiter);
  std::istream & operator>>(std::istream & in, KeyI && keyStub);
  std::istream & operator>>(std::istream & in, DoubleLitI && doubleLit);
}

#endif
