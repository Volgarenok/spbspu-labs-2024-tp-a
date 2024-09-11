#ifndef INPUT_FORMATTERS_HPP
#define INPUT_FORMATTERS_HPP

#include <complex>
#include <istream>
#include <string>

namespace ibragimov
{
  namespace formatters
  {
    struct DoubleLitI
    {
      double& reference;
    };
    std::istream& operator>>(std::istream&, DoubleLitI&&);
    struct ComplexLspI
    {
      std::complex< double >& reference;
    };
    std::istream& operator>>(std::istream&, ComplexLspI&&);
    struct StringI
    {
      std::string& reference;
    };
    std::istream& operator>>(std::istream&, StringI&&);
  }
}

#endif
