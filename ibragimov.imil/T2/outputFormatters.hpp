#ifndef OUTPUT_FORMATTERS_HPP
#define OUTPUT_FORMATTERS_HPP

#include <complex>
#include <iostream>
#include <string>

namespace ibragimov
{
  struct DoubleLitO
  {
    double& ref;
  };
  std::ostream& operator<<(std::ostream&, const DoubleLitO&&);

  struct ComplexLspO
  {
    std::complex<double>& ref;
  };
  std::ostream& operator<<(std::ostream&, const ComplexLspO&&);

  struct StringO
  {
    std::string& ref;
  };
  std::ostream& operator<<(std::ostream&, const StringO&&);
}

#endif
