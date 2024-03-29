#ifndef OUTPUT_FORMATTERS_HPP
#define OUTPUT_FORMATTERS_HPP

#include <complex>
#include <ostream>
#include <string>

namespace ibragimov
{
  struct DoubleLitO
  {
    const double& ref;
  };
  std::ostream& operator<<(std::ostream&, const DoubleLitO&&);

  struct ComplexLspO
  {
    const std::complex<double>& ref;
  };
  std::ostream& operator<<(std::ostream&, const ComplexLspO&&);

  struct StringO
  {
    const std::string& ref;
  };
  std::ostream& operator<<(std::ostream&, const StringO&&);
}

#endif
