#ifndef DELIMETERS_HPP
#define DELIMETERS_HPP

#include <iostream>

namespace namestnikov
{
  struct DelimeterChar
  {
    char delimeter;
  };

  struct DelimeterString
  {
    const char * delimeter;
  };

  struct DelimeterLetter
  {
    char delimeter;
  };
  std::istream & operator>>(std::istream & in, DelimeterChar && del);
  std::istream & operator>>(std::istream & in, DelimeterString && del);
  std::istream & operator>>(std::istream & in, DelimeterLetter && del);
}

#endif