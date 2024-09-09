#ifndef VALUE_I_HPP
#define VALUE_I_HPP

#include <string>
#include <istream>

namespace novikov
{
  struct OctValueI
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, OctValueI&& val);

  struct HexValueI
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, HexValueI&& val);

  struct StrValueI
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, StrValueI&& val);
}

#endif
