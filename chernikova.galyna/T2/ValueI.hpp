#ifndef VALUEI_HPP
#define VALUEI_HPP

#include <iostream>

namespace chernikova
{
  struct DoubleI
  {
    double& ref;
  };

  struct UnsignedllI
  {
    unsigned long long& ref;
  };

  struct StringI
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, chernikova::DoubleI&& exp);
  std::istream& operator>>(std::istream& in, chernikova::UnsignedllI&& exp);
  std::istream& operator>>(std::istream& in, chernikova::StringI&& dest);
}

#endif
