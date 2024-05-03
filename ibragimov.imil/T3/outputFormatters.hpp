#ifndef OUTPUT_FORMATTERS_HPP
#define OUTPUT_FORMATTERS_HPP

#include <iostream>

namespace ibragimov
{
  struct AreaO
  {
    double& ref;
  };
  std::ostream& operator<<(std::ostream&, AreaO&&);
}

#endif
