#ifndef VALUEIO_HPP
#define VALUEIO_HPP

#include <iostream>
#include <string>

namespace chernikova
{
  struct DoubleI
  {
    double& ref;
  };

  struct DoubleO
  {
    double ref;
  };

  struct UnsignedllI
  {
    unsigned long long& ref;
  };

  struct StringI
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DoubleI&& exp);
  std::ostream& operator<<(std::ostream& out, const DoubleO&& exp);
  std::istream& operator>>(std::istream& in, UnsignedllI&& exp);
  std::istream& operator>>(std::istream& in, StringI&& dest);
}

#endif
