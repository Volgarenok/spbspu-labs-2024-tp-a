#ifndef WRAPPERS_HPP
#define WRAPPERS_HPP

#include <istream>

namespace ravinskij {

  struct BinUll
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, BinUll&& num);

  constexpr size_t getUllSize()
  {
    return 64;
  }

  constexpr size_t getInputSize()
  {
    return 2;
  }

  struct HexUll
  {
    unsigned long long& value;
  };
  std::istream& operator>>(std::istream& in, HexUll&& num);
}
#endif
