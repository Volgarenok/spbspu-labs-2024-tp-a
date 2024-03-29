#ifndef INPUT_FORMATTERS_HPP
#define INPUT_FORMATTERS_HPP

#include <complex>
#include <istream>
#include <string>

namespace ibragimov
{
  struct KeyIdI
  {
    int& ref;
  };
  std::istream& operator>>(std::istream&, KeyIdI&&);

  struct DoubleLitI
  {
    double& ref;
  };
  std::istream& operator>>(std::istream&, DoubleLitI&&);

  struct ComplexLspI
  {
    std::complex<double>& ref;
  };
  std::istream& operator>>(std::istream&, ComplexLspI&&);

  struct StringI
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream&, StringI&&);
}

#endif
