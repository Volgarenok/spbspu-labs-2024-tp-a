#ifndef INFORMATTERS_HPP
#define INFORMATTERS_HPP

#include <iosfwd>
#include <string>

namespace arakelyan
{
  struct OctUllIO
  {
    unsigned long long &ref;
  };

  struct CharLitIO
  {
    char &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  std::istream &operator>>(std::istream &in, OctUllIO &&dest);
  std::istream &operator>>(std::istream &in, CharLitIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
}

#endif
