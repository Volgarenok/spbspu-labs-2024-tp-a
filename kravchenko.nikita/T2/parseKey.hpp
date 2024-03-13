#ifndef PARSE_KEY_HPP
#define PARSE_KEY_HPP

#include <istream>
#include <complex>
#include <string>

namespace kravchenko
{
  struct SignedLLKey
  {
    long long& value;
  };
  std::istream& operator>>(std::istream& in, SignedLLKey&& key);

  struct ComplexKey
  {
    std::complex< double >& value;
  };
  std::istream& operator>>(std::istream& in, ComplexKey&& key);

  struct StringKey
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, StringKey&& key);
}

#endif
