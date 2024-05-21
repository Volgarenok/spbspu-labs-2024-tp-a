#ifndef KEYS_HPP
#define KEYS_HPP

#include <istream>
#include <complex>
#include <string>

namespace kuznetsov
{
  struct UllKey
  {
    unsigned long long& data;
  };
  std::istream& operator>>(std::istream& in, UllKey&& key);

  struct ComplexKey
  {
    std::complex< double >& data;
  };
  std::istream& operator>>(std::istream& in, ComplexKey&& key);

  struct StringKey
  {
    std::string& line;
  };
  std::istream& operator>>(std::istream& in, StringKey&& key);
}

#endif

