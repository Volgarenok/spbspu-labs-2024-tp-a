#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <string>
#include <iosfwd>
#include <iostream>

namespace vojuck
{
  struct DelimiterIO
  {
    char exp;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct HexULL
  {
    unsigned long long &ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  struct CharIO
  {
    char &ref;
  };
std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, StringIO &&dest);
std::istream &operator>>(std::istream &in, HexULL &&dest);
std::istream &operator>>(std::istream &in, LabelIO &&dest);
std::istream &operator>>(std::istream &in, CharIO &&dest);
}
#endif
