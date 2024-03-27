#ifndef WRAPPERS_HPP
#define WRAPPERS_HPP

#include <istream>

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
}
#endif
