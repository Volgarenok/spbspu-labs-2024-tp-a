#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>

#include "../common/delimiter.hpp"

namespace kovtun
{
  struct KeyI
  {
    int & number;
  };

  struct DoubleLitI
  {
    double & dl;
  };

  struct CharLitI
  {
    char & cl;
  };

  struct StringI
  {
    std::string & data;
  };

  std::istream & operator>>(std::istream & in, KeyI && keyStub);
  std::istream & operator>>(std::istream & in, DoubleLitI && doubleLit);
  std::istream & operator>>(std::istream & in, CharLitI && charLit);
  std::istream & operator>>(std::istream & in, StringI && str);
}

#endif
