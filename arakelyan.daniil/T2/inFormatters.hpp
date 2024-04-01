#ifndef INFORMATTERS_HPP
#define INFORMATTERS_HPP

#include <iostream>
#include <string>

namespace arakelyan
{
  struct OctUll
  {
    unsigned long long &ref;
  };

  struct CharLit
  {
    char &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  std::istream &operator>>(std::istream &in, OctUll &&dest);
  std::istream &operator>>(std::istream &in, CharLit &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
}

#endif
