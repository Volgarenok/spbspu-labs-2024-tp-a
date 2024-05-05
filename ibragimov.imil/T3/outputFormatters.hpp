#ifndef OUTPUT_FORMATTERS_HPP
#define OUTPUT_FORMATTERS_HPP

#include <iostream>

namespace ibragimov
{
  struct AreaO
  {
    const double& ref = 0;
  };
  std::ostream& operator<<(std::ostream&, const AreaO&&);
}

#endif
