#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iostream>
#include <string>
namespace vorobieva
{
  struct DelimiterChar
  {
    char expected;
  };

  struct DelimiterString
  {
  const char * expected;
  };

  std::istream & operator>>(std::istream & in, DelimiterChar && exp);
  std::istream & operator>>(std::istream & in, DelimiterString && exp);
}

#endif
