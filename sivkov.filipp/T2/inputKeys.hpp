#ifndef INPUTKEYS_HPP
#define INPUTKEYS_HPP

#include <istream>
#include <complex>
#include <string>

namespace sivkov
{
  struct DoubleKey
  {
    double& num;
  };

  struct ComplexKey
  {
    std::complex< double >& num;
  };

  struct StringKey
  {
    std::string& string;
  };

  std::istream& operator>>(std::istream& input, DoubleKey&& key);
  std::istream& operator>>(std::istream& input, ComplexKey&& key);
  std::istream& operator>>(std::istream& input, StringKey&& key);
}

#endif
