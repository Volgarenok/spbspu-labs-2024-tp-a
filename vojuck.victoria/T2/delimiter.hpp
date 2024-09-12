#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <string>
#include <iosfwd>
#include <iostream>

namespace vojuck
{
  struct DelimeterIO
  {
    char exp;
  };

  struct StringIO
  {
    std::string &ref
  };

  struct HexULL
  {
    unsigned long long &ref
  };

  struct LablelIO
  {
    std::string exp;
  };

  struct CharIO
  {
    char &ref
  }
std::istream operator>>(std::istream &in, DelimeterIO &&dest);
std::istream operator>>(std::istream &in, StringIO &&dest);
std::istream operator>>(std::istream &in, HexULL &&dest);
std::istream operator>>(std::istream &in, LablelIO &&dest);
std::istream operator>>(std::istream &in, CharIO &&dest);
}
#endif
