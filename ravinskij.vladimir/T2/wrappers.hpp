#ifndef WRAPPERS_HPP
#define WRAPPERS_HPP

#include <istream>
#include <string>

namespace ravinskij {

  struct BinUll
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, BinUll&& num);

  struct HexUll
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, HexUll&& num);

  struct StrKey
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, StrKey&& value);
}
#endif
