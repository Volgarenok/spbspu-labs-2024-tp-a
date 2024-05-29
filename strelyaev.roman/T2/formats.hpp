#ifndef FORMATS_HPP
#define FORAMTS_HPP
#include <iosfwd>
#include <string>

namespace strelyaev
{
  struct Litll
  {
    long long& value;
  };
  std::istream& operator>>(std::istream& in, Litll&& num);

  struct HexUll
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, HexUll&& num);

  struct StringKey
  {
    std::string& str;
  };
  std::istream& operator>>(std::istream& in, StringKey&& num);
}
#endif
