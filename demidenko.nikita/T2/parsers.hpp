#ifndef PARSERS_HPP
#define PARSERS_HPP

#include <complex>
#include <iosfwd>
#include <string>
#include "keysEnum.hpp"

namespace demidenko
{
  struct KeyI
  {
    KeysEnum& key;
  };
  std::istream& operator>>(std::istream& in, KeyI&& parser);

  struct ComplexI
  {
    std::complex< double >& complex;
  };
  std::istream& operator>>(std::istream& in, ComplexI&& parser);

  struct UnsignedLongLongI
  {
    unsigned long long& ull;
  };
  std::istream& operator>>(std::istream& in, UnsignedLongLongI&& parser);

  struct StringI
  {
    std::string& str;
  };
  std::istream& operator>>(std::istream& in, StringI&& parser);
}

#endif
