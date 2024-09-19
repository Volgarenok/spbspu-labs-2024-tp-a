#ifndef DOUBLE_O_HPP
#define DOUBLE_O_HPP

#include "iosfwd"

namespace sazanov
{
  struct DoubleO
  {
    const double& number;
  };
  std::ostream& operator<<(std::ostream& out, const DoubleO&& value);
}

#endif
