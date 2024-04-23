#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <iostream>
#include <utility>
#include <cstring>

namespace chistyakov
{
  struct UllBinIO
  {
    unsigned long long & value;
  };
  std::istream & operator>>(std::istream & in, UllBinIO && data);
  std::ostream & operator<<(std::ostream & out, UllBinIO && data);

  struct RatLspIO
  {
    std::pair< long long, unsigned long long > & value;
  };
  std::istream & operator>>(std::istream & in, RatLspIO && data);

  struct StringIO
  {
    std::string & value;
  };
  std::istream & operator>>(std::istream &, StringIO && data);
}

#endif
