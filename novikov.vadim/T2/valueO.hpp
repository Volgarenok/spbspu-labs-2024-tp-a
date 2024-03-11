#ifndef VALUE_O_HPP
#define VALUE_O_HPP

#include <string>
#include <ostream>

namespace novikov
{
  struct OctValueO
  {
    const unsigned long long& value;
  };
  std::ostream& operator<<(std::istream& out, const OctValueO& val);

  struct HexValueO
  {
    const unsigned long long& value;
  };
  std::ostream& operator<<(std::istream& out, const HexValueO& val);

  struct StrValueO
  {
    const std::string& value;
  };
  std::ostream& operator<<(std::istream& out, const StrValueO& val);
}

#endif
