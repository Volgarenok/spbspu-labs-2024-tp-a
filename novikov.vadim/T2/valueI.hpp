#ifndef VALUE_I_HPP
#define VALUE_I_HPP

#include <string>
#include <iostream>

namespace novikov
{
  struct OctValueI
  {
    unsigned long long expected;
  };
  std::istream& operator>>(std::istream& in, OctValueI& exp);
  std::ostream& operator<<(std::ostream& out, const OctValueI& exp);

  struct HexValueI
  {
    unsigned long long expected;
  };
  std::istream& operator>>(std::istream& in, HexValueI& exp);
  std::ostream& operator<<(std::ostream& out, const HexValueI& exp);

  struct StrValueI
  {
    std::string expected;
  };
  std::istream& operator>>(std::istream& in, StrValueI& exp);
  std::ostream& operator<<(std::ostream& out, const StrValueI& exp);
}

#endif