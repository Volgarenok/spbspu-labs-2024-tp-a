#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <string>
#include <iosfwd>
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

  struct UnsignedLL
  {
    unsigned long long &ref
  };

  struct LableIO
  {
    std::string exp;
  };

  struct CharIO
  {
    char &ref
  }
std::istream operator>>(std::istream &in, DelimeterIO &&dest);
std::istream operator>>(std::istream &in, StringIO &&dest);
std::istream operator>>(std::istream &in, UnsignedLL &&dest);
std::istream operator>>(std::istream &in, LableIO &&dest);
std::istream operator>>(std::istream &in, CharIO &&dest);
}
#endif
