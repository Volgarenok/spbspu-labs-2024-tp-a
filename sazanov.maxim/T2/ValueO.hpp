#ifndef VALUE_O_HPP
#define VALUE_O_HPP

#include <iosfwd>

namespace sazanov
{
  struct BinUllValueO
  {
    const unsigned long long& number;
  };
  std::ostream& operator<<(std::ostream& out, const BinUllValueO& value);
  int getNumberOfBits(unsigned long long val);
}

#endif
