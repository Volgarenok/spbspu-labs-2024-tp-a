#ifndef KEY_INPUT_HPP
#define KEY_INPUT_HPP

#include <string>
#include <iostream>

namespace prisyach
{
  struct FirstKey
  {
    double & data;
  };
  std::istream & operator>>(std::istream & in, FirstKey && key);

  struct SecondKey
  {
    unsigned long long & data;
  };
  std::istream & operator>>(std::istream & in, SecondKey && key);

  struct ThirdKey
  {
    std::string & data;
  };
  std::istream & operator>>(std::istream & in, ThirdKey && key);
}

#endif